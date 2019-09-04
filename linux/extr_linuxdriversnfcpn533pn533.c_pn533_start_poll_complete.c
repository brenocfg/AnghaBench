#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int len; scalar_t__* data; } ;
struct pn533 {int poll_protocols; int poll_dep; } ;

/* Variables and functions */
 int EAGAIN ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 int pn533_target_found (struct pn533*,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static int pn533_start_poll_complete(struct pn533 *dev, struct sk_buff *resp)
{
	u8 nbtg, tg, *tgdata;
	int rc, tgdata_len;

	/* Toggle the DEP polling */
	if (dev->poll_protocols & NFC_PROTO_NFC_DEP_MASK)
		dev->poll_dep = 1;

	nbtg = resp->data[0];
	tg = resp->data[1];
	tgdata = &resp->data[2];
	tgdata_len = resp->len - 2;  /* nbtg + tg */

	if (nbtg) {
		rc = pn533_target_found(dev, tg, tgdata, tgdata_len);

		/* We must stop the poll after a valid target found */
		if (rc == 0)
			return 0;
	}

	return -EAGAIN;
}