#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_1__* up; } ;
struct cffrml {scalar_t__ dofcs; } ;
struct TYPE_2__ {int (* receive ) (TYPE_1__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  cffrml_checksum ; 
 int /*<<< orphan*/  cffrml_rcv_checsum_error ; 
 int /*<<< orphan*/  cffrml_rcv_error ; 
 int /*<<< orphan*/  cfpkt_add_trail (struct cfpkt*,int*,int) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_erroneous (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_extr_head (struct cfpkt*,int*,int) ; 
 int /*<<< orphan*/  cfpkt_extr_trail (struct cfpkt*,int*,int) ; 
 int cfpkt_iterate (struct cfpkt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cfpkt_setlen (struct cfpkt*,int) ; 
 struct cffrml* container_obj (struct cflayer*) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 

__attribute__((used)) static int cffrml_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u16 tmp;
	u16 len;
	u16 hdrchks;
	int pktchks;
	struct cffrml *this;
	this = container_obj(layr);

	cfpkt_extr_head(pkt, &tmp, 2);
	len = le16_to_cpu(tmp);

	/* Subtract for FCS on length if FCS is not used. */
	if (!this->dofcs)
		len -= 2;

	if (cfpkt_setlen(pkt, len) < 0) {
		++cffrml_rcv_error;
		pr_err("Framing length error (%d)\n", len);
		cfpkt_destroy(pkt);
		return -EPROTO;
	}
	/*
	 * Don't do extract if FCS is false, rather do setlen - then we don't
	 * get a cache-miss.
	 */
	if (this->dofcs) {
		cfpkt_extr_trail(pkt, &tmp, 2);
		hdrchks = le16_to_cpu(tmp);
		pktchks = cfpkt_iterate(pkt, cffrml_checksum, 0xffff);
		if (pktchks != hdrchks) {
			cfpkt_add_trail(pkt, &tmp, 2);
			++cffrml_rcv_error;
			++cffrml_rcv_checsum_error;
			pr_info("Frame checksum error (0x%x != 0x%x)\n",
				hdrchks, pktchks);
			return -EILSEQ;
		}
	}
	if (cfpkt_erroneous(pkt)) {
		++cffrml_rcv_error;
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}

	if (layr->up == NULL) {
		pr_err("Layr up is missing!\n");
		cfpkt_destroy(pkt);
		return -EINVAL;
	}

	return layr->up->receive(layr->up, pkt);
}