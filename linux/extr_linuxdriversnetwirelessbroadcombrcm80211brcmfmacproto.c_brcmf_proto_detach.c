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
struct brcmf_pub {int /*<<< orphan*/ * proto; TYPE_1__* bus_if; } ;
struct TYPE_2__ {scalar_t__ proto_type; } ;

/* Variables and functions */
 scalar_t__ BRCMF_PROTO_BCDC ; 
 scalar_t__ BRCMF_PROTO_MSGBUF ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_proto_bcdc_detach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_proto_msgbuf_detach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void brcmf_proto_detach(struct brcmf_pub *drvr)
{
	brcmf_dbg(TRACE, "Enter\n");

	if (drvr->proto) {
		if (drvr->bus_if->proto_type == BRCMF_PROTO_BCDC)
			brcmf_proto_bcdc_detach(drvr);
		else if (drvr->bus_if->proto_type == BRCMF_PROTO_MSGBUF)
			brcmf_proto_msgbuf_detach(drvr);
		kfree(drvr->proto);
		drvr->proto = NULL;
	}
}