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
struct smp_ltk {int /*<<< orphan*/  enc_size; int /*<<< orphan*/  val; int /*<<< orphan*/  rand; int /*<<< orphan*/  ediv; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_conn {int /*<<< orphan*/  flags; int /*<<< orphan*/  enc_key_size; int /*<<< orphan*/  role; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 int /*<<< orphan*/  HCI_CONN_STK_ENCRYPT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct smp_ltk* hci_find_ltk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_le_start_enc (struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smp_ltk_sec_level (struct smp_ltk*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool smp_ltk_encrypt(struct l2cap_conn *conn, u8 sec_level)
{
	struct smp_ltk *key;
	struct hci_conn *hcon = conn->hcon;

	key = hci_find_ltk(hcon->hdev, &hcon->dst, hcon->dst_type, hcon->role);
	if (!key)
		return false;

	if (smp_ltk_sec_level(key) < sec_level)
		return false;

	if (test_and_set_bit(HCI_CONN_ENCRYPT_PEND, &hcon->flags))
		return true;

	hci_le_start_enc(hcon, key->ediv, key->rand, key->val, key->enc_size);
	hcon->enc_key_size = key->enc_size;

	/* We never store STKs for master role, so clear this flag */
	clear_bit(HCI_CONN_STK_ENCRYPT, &hcon->flags);

	return true;
}