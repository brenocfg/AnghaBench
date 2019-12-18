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
struct hci_conn {scalar_t__ enc_key_size; TYPE_1__* hdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ min_enc_key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool l2cap_check_enc_key_size(struct hci_conn *hcon)
{
	/* The minimum encryption key size needs to be enforced by the
	 * host stack before establishing any L2CAP connections. The
	 * specification in theory allows a minimum of 1, but to align
	 * BR/EDR and LE transports, a minimum of 7 is chosen.
	 *
	 * This check might also be called for unencrypted connections
	 * that have no key size requirements. Ensure that the link is
	 * actually encrypted before enforcing a key size.
	 */
	return (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags) ||
		hcon->enc_key_size >= hcon->hdev->min_enc_key_size);
}