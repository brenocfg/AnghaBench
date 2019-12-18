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
struct sk_buff {unsigned char* data; } ;
struct accessdata_dn {scalar_t__ acc_userl; scalar_t__ acc_passl; scalar_t__ acc_accl; int /*<<< orphan*/  acc_acc; int /*<<< orphan*/  acc_pass; int /*<<< orphan*/  acc_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void dn_access_copy(struct sk_buff *skb, struct accessdata_dn *acc)
{
	unsigned char *ptr = skb->data;

	acc->acc_userl = *ptr++;
	memcpy(&acc->acc_user, ptr, acc->acc_userl);
	ptr += acc->acc_userl;

	acc->acc_passl = *ptr++;
	memcpy(&acc->acc_pass, ptr, acc->acc_passl);
	ptr += acc->acc_passl;

	acc->acc_accl = *ptr++;
	memcpy(&acc->acc_acc, ptr, acc->acc_accl);

	skb_pull(skb, acc->acc_accl + acc->acc_passl + acc->acc_userl + 3);

}