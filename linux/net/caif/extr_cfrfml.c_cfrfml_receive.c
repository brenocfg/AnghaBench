#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_5__* up; } ;
struct TYPE_8__ {TYPE_2__ dev_info; TYPE_1__ layer; } ;
struct cfrfml {scalar_t__ pdu_size; int /*<<< orphan*/  sync; TYPE_3__ serv; struct cfpkt* incomplete_frm; scalar_t__ seghead; } ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_4__* up; int /*<<< orphan*/ * receive; } ;
struct TYPE_10__ {int (* receive ) (TYPE_5__*,struct cfpkt*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND ; 
 int EAGAIN ; 
 int EIO ; 
 int EPROTO ; 
 scalar_t__ RFM_HEAD_SIZE ; 
 int RFM_SEGMENTATION_BIT ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_erroneous (struct cfpkt*) ; 
 scalar_t__ cfpkt_extr_head (struct cfpkt*,int*,int) ; 
 scalar_t__ cfpkt_getlen (struct cfpkt*) ; 
 scalar_t__ cfpkt_peek_head (struct cfpkt*,scalar_t__,int) ; 
 struct cfrfml* container_obj (struct cflayer*) ; 
 scalar_t__ get_unaligned_le16 (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct cfpkt* rfm_append (struct cfrfml*,int*,struct cfpkt*,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*,struct cfpkt*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cfrfml_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u8 tmp;
	bool segmented;
	int err;
	u8 seghead[6];
	struct cfrfml *rfml;
	struct cfpkt *tmppkt = NULL;

	caif_assert(layr->up != NULL);
	caif_assert(layr->receive != NULL);
	rfml = container_obj(layr);
	spin_lock(&rfml->sync);

	err = -EPROTO;
	if (cfpkt_extr_head(pkt, &tmp, 1) < 0)
		goto out;
	segmented = tmp & RFM_SEGMENTATION_BIT;

	if (segmented) {
		if (rfml->incomplete_frm == NULL) {
			/* Initial Segment */
			if (cfpkt_peek_head(pkt, rfml->seghead, 6) < 0)
				goto out;

			rfml->pdu_size = get_unaligned_le16(rfml->seghead+4);

			if (cfpkt_erroneous(pkt))
				goto out;
			rfml->incomplete_frm = pkt;
			pkt = NULL;
		} else {

			tmppkt = rfm_append(rfml, seghead, pkt, &err);
			if (tmppkt == NULL)
				goto out;

			if (cfpkt_erroneous(tmppkt))
				goto out;

			rfml->incomplete_frm = tmppkt;


			if (cfpkt_erroneous(tmppkt))
				goto out;
		}
		err = 0;
		goto out;
	}

	if (rfml->incomplete_frm) {

		/* Last Segment */
		tmppkt = rfm_append(rfml, seghead, pkt, &err);
		if (tmppkt == NULL)
			goto out;

		if (cfpkt_erroneous(tmppkt))
			goto out;

		rfml->incomplete_frm = NULL;
		pkt = tmppkt;
		tmppkt = NULL;

		/* Verify that length is correct */
		err = -EPROTO;
		if (rfml->pdu_size != cfpkt_getlen(pkt) - RFM_HEAD_SIZE + 1)
			goto out;
	}

	err = rfml->serv.layer.up->receive(rfml->serv.layer.up, pkt);

out:

	if (err != 0) {
		if (tmppkt)
			cfpkt_destroy(tmppkt);
		if (pkt)
			cfpkt_destroy(pkt);
		if (rfml->incomplete_frm)
			cfpkt_destroy(rfml->incomplete_frm);
		rfml->incomplete_frm = NULL;

		pr_info("Connection error %d triggered on RFM link\n", err);

		/* Trigger connection error upon failure.*/
		layr->up->ctrlcmd(layr->up, CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND,
					rfml->serv.dev_info.id);
	}
	spin_unlock(&rfml->sync);

	if (unlikely(err == -EAGAIN))
		/* It is not possible to recover after drop of a fragment */
		err = -EIO;

	return err;
}