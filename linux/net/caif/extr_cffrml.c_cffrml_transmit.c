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
typedef  int /*<<< orphan*/  u16 ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_1__* dn; } ;
struct cffrml {scalar_t__ dofcs; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int hdr_len; } ;
struct TYPE_3__ {int (* transmit ) (TYPE_1__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int EPROTO ; 
 int /*<<< orphan*/  cffrml_checksum ; 
 int /*<<< orphan*/  cfpkt_add_head (struct cfpkt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfpkt_add_trail (struct cfpkt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_erroneous (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_getlen (struct cfpkt*) ; 
 TYPE_2__* cfpkt_info (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_iterate (struct cfpkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfpkt_pad_trail (struct cfpkt*,int) ; 
 struct cffrml* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 

__attribute__((used)) static int cffrml_transmit(struct cflayer *layr, struct cfpkt *pkt)
{
	u16 chks;
	u16 len;
	__le16 data;

	struct cffrml *this = container_obj(layr);
	if (this->dofcs) {
		chks = cfpkt_iterate(pkt, cffrml_checksum, 0xffff);
		data = cpu_to_le16(chks);
		cfpkt_add_trail(pkt, &data, 2);
	} else {
		cfpkt_pad_trail(pkt, 2);
	}
	len = cfpkt_getlen(pkt);
	data = cpu_to_le16(len);
	cfpkt_add_head(pkt, &data, 2);
	cfpkt_info(pkt)->hdr_len += 2;
	if (cfpkt_erroneous(pkt)) {
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}

	if (layr->dn == NULL) {
		cfpkt_destroy(pkt);
		return -ENODEV;

	}
	return layr->dn->transmit(layr->dn, pkt);
}