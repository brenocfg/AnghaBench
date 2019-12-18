#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_2__ dev_info; } ;
struct cfrfml {scalar_t__ fragment_size; TYPE_4__ serv; } ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_3__* up; TYPE_1__* dn; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * transmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND ; 
 int EPROTO ; 
 int RFM_HEAD_SIZE ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ cfpkt_add_head (struct cfpkt*,int*,int) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_getlen (struct cfpkt*) ; 
 int cfpkt_peek_head (struct cfpkt*,int*,int) ; 
 struct cfpkt* cfpkt_split (struct cfpkt*,scalar_t__) ; 
 int cfrfml_transmit_segment (struct cfrfml*,struct cfpkt*) ; 
 int /*<<< orphan*/  cfsrvl_ready (TYPE_4__*,int*) ; 
 struct cfrfml* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfrfml_transmit(struct cflayer *layr, struct cfpkt *pkt)
{
	int err;
	u8 seg;
	u8 head[6];
	struct cfpkt *rearpkt = NULL;
	struct cfpkt *frontpkt = pkt;
	struct cfrfml *rfml = container_obj(layr);

	caif_assert(layr->dn != NULL);
	caif_assert(layr->dn->transmit != NULL);

	if (!cfsrvl_ready(&rfml->serv, &err))
		goto out;

	err = -EPROTO;
	if (cfpkt_getlen(pkt) <= RFM_HEAD_SIZE-1)
		goto out;

	err = 0;
	if (cfpkt_getlen(pkt) > rfml->fragment_size + RFM_HEAD_SIZE)
		err = cfpkt_peek_head(pkt, head, 6);

	if (err < 0)
		goto out;

	while (cfpkt_getlen(frontpkt) > rfml->fragment_size + RFM_HEAD_SIZE) {

		seg = 1;
		err = -EPROTO;

		if (cfpkt_add_head(frontpkt, &seg, 1) < 0)
			goto out;
		/*
		 * On OOM error cfpkt_split returns NULL.
		 *
		 * NOTE: Segmented pdu is not correctly aligned.
		 * This has negative performance impact.
		 */

		rearpkt = cfpkt_split(frontpkt, rfml->fragment_size);
		if (rearpkt == NULL)
			goto out;

		err = cfrfml_transmit_segment(rfml, frontpkt);

		if (err != 0) {
			frontpkt = NULL;
			goto out;
		}

		frontpkt = rearpkt;
		rearpkt = NULL;

		err = -EPROTO;
		if (cfpkt_add_head(frontpkt, head, 6) < 0)
			goto out;

	}

	seg = 0;
	err = -EPROTO;

	if (cfpkt_add_head(frontpkt, &seg, 1) < 0)
		goto out;

	err = cfrfml_transmit_segment(rfml, frontpkt);

	frontpkt = NULL;
out:

	if (err != 0) {
		pr_info("Connection error %d triggered on RFM link\n", err);
		/* Trigger connection error upon failure.*/

		layr->up->ctrlcmd(layr->up, CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND,
					rfml->serv.dev_info.id);

		if (rearpkt)
			cfpkt_destroy(rearpkt);

		if (frontpkt)
			cfpkt_destroy(frontpkt);
	}

	return err;
}