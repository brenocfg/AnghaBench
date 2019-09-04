#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_3__ {TYPE_2__* up; } ;
struct cfserl {int /*<<< orphan*/  sync; scalar_t__ usestx; TYPE_1__ layer; struct cfpkt* incomplete_frm; } ;
struct cfpkt {int dummy; } ;
struct cflayer {int dummy; } ;
struct TYPE_4__ {int (* receive ) (TYPE_2__*,struct cfpkt*) ;} ;

/* Variables and functions */
 scalar_t__ CFSERL_STX ; 
 int EILSEQ ; 
 int ENOMEM ; 
 int EPROTO ; 
 int SERIAL_MAX_FRAMESIZE ; 
 int SERIAL_MINIUM_PACKET_SIZE ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_add_head (struct cfpkt*,scalar_t__*,int) ; 
 void* cfpkt_append (struct cfpkt*,struct cfpkt*,int) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_extr_head (struct cfpkt*,scalar_t__*,int) ; 
 int cfpkt_getlen (struct cfpkt*) ; 
 scalar_t__ cfpkt_more (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_peek_head (struct cfpkt*,int*,int) ; 
 struct cfpkt* cfpkt_split (struct cfpkt*,int) ; 
 struct cfserl* container_obj (struct cflayer*) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,struct cfpkt*) ; 

__attribute__((used)) static int cfserl_receive(struct cflayer *l, struct cfpkt *newpkt)
{
	struct cfserl *layr = container_obj(l);
	u16 pkt_len;
	struct cfpkt *pkt = NULL;
	struct cfpkt *tail_pkt = NULL;
	u8 tmp8;
	u16 tmp;
	u8 stx = CFSERL_STX;
	int ret;
	u16 expectlen = 0;

	caif_assert(newpkt != NULL);
	spin_lock(&layr->sync);

	if (layr->incomplete_frm != NULL) {
		layr->incomplete_frm =
		    cfpkt_append(layr->incomplete_frm, newpkt, expectlen);
		pkt = layr->incomplete_frm;
		if (pkt == NULL) {
			spin_unlock(&layr->sync);
			return -ENOMEM;
		}
	} else {
		pkt = newpkt;
	}
	layr->incomplete_frm = NULL;

	do {
		/* Search for STX at start of pkt if STX is used */
		if (layr->usestx) {
			cfpkt_extr_head(pkt, &tmp8, 1);
			if (tmp8 != CFSERL_STX) {
				while (cfpkt_more(pkt)
				       && tmp8 != CFSERL_STX) {
					cfpkt_extr_head(pkt, &tmp8, 1);
				}
				if (!cfpkt_more(pkt)) {
					cfpkt_destroy(pkt);
					layr->incomplete_frm = NULL;
					spin_unlock(&layr->sync);
					return -EPROTO;
				}
			}
		}

		pkt_len = cfpkt_getlen(pkt);

		/*
		 *  pkt_len is the accumulated length of the packet data
		 *  we have received so far.
		 *  Exit if frame doesn't hold length.
		 */

		if (pkt_len < 2) {
			if (layr->usestx)
				cfpkt_add_head(pkt, &stx, 1);
			layr->incomplete_frm = pkt;
			spin_unlock(&layr->sync);
			return 0;
		}

		/*
		 *  Find length of frame.
		 *  expectlen is the length we need for a full frame.
		 */
		cfpkt_peek_head(pkt, &tmp, 2);
		expectlen = le16_to_cpu(tmp) + 2;
		/*
		 * Frame error handling
		 */
		if (expectlen < SERIAL_MINIUM_PACKET_SIZE
		    || expectlen > SERIAL_MAX_FRAMESIZE) {
			if (!layr->usestx) {
				if (pkt != NULL)
					cfpkt_destroy(pkt);
				layr->incomplete_frm = NULL;
				expectlen = 0;
				spin_unlock(&layr->sync);
				return -EPROTO;
			}
			continue;
		}

		if (pkt_len < expectlen) {
			/* Too little received data */
			if (layr->usestx)
				cfpkt_add_head(pkt, &stx, 1);
			layr->incomplete_frm = pkt;
			spin_unlock(&layr->sync);
			return 0;
		}

		/*
		 * Enough data for at least one frame.
		 * Split the frame, if too long
		 */
		if (pkt_len > expectlen)
			tail_pkt = cfpkt_split(pkt, expectlen);
		else
			tail_pkt = NULL;

		/* Send the first part of packet upwards.*/
		spin_unlock(&layr->sync);
		ret = layr->layer.up->receive(layr->layer.up, pkt);
		spin_lock(&layr->sync);
		if (ret == -EILSEQ) {
			if (layr->usestx) {
				if (tail_pkt != NULL)
					pkt = cfpkt_append(pkt, tail_pkt, 0);
				/* Start search for next STX if frame failed */
				continue;
			} else {
				cfpkt_destroy(pkt);
				pkt = NULL;
			}
		}

		pkt = tail_pkt;

	} while (pkt != NULL);

	spin_unlock(&layr->sync);
	return 0;
}