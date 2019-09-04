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
struct sk_buff {int dummy; } ;
struct nfc_llcp_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfc_llcp_recv (struct nfc_llcp_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

void nfc_llcp_recv(void *data, struct sk_buff *skb, int err)
{
	struct nfc_llcp_local *local = (struct nfc_llcp_local *) data;

	pr_debug("Received an LLCP PDU\n");
	if (err < 0) {
		pr_err("err %d\n", err);
		return;
	}

	__nfc_llcp_recv(local, skb);
}