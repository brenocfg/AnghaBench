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
struct hci_conn {scalar_t__ sec_level; int /*<<< orphan*/  role; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; int /*<<< orphan*/  flags; } ;
typedef  enum smp_key_pref { ____Placeholder_smp_key_pref } smp_key_pref ;

/* Variables and functions */
 scalar_t__ BT_SECURITY_LOW ; 
 int /*<<< orphan*/  HCI_CONN_STK_ENCRYPT ; 
 int SMP_USE_LTK ; 
 scalar_t__ hci_find_ltk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool smp_sufficient_security(struct hci_conn *hcon, u8 sec_level,
			     enum smp_key_pref key_pref)
{
	if (sec_level == BT_SECURITY_LOW)
		return true;

	/* If we're encrypted with an STK but the caller prefers using
	 * LTK claim insufficient security. This way we allow the
	 * connection to be re-encrypted with an LTK, even if the LTK
	 * provides the same level of security. Only exception is if we
	 * don't have an LTK (e.g. because of key distribution bits).
	 */
	if (key_pref == SMP_USE_LTK &&
	    test_bit(HCI_CONN_STK_ENCRYPT, &hcon->flags) &&
	    hci_find_ltk(hcon->hdev, &hcon->dst, hcon->dst_type, hcon->role))
		return false;

	if (hcon->sec_level >= sec_level)
		return true;

	return false;
}