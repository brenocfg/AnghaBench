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
struct hci_conn {scalar_t__ type; scalar_t__ key_type; int pin_length; int /*<<< orphan*/  enc_key_size; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  BT_SECURITY_FIPS ; 
 int /*<<< orphan*/  BT_SECURITY_HIGH ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int /*<<< orphan*/  BT_SECURITY_MEDIUM ; 
 int /*<<< orphan*/  BT_SECURITY_SDP ; 
 int /*<<< orphan*/  HCI_CONN_AUTH ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_INITIATOR ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 scalar_t__ HCI_LK_AUTH_COMBINATION_P192 ; 
 scalar_t__ HCI_LK_AUTH_COMBINATION_P256 ; 
 scalar_t__ HCI_LK_COMBINATION ; 
 scalar_t__ HCI_LK_UNAUTH_COMBINATION_P192 ; 
 scalar_t__ HCI_LK_UNAUTH_COMBINATION_P256 ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  hci_conn_auth (struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_encrypt (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_ssp_enabled (struct hci_conn*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_conn_security (struct hci_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_conn_security(struct hci_conn *conn, __u8 sec_level, __u8 auth_type,
		      bool initiator)
{
	BT_DBG("hcon %p", conn);

	if (conn->type == LE_LINK)
		return smp_conn_security(conn, sec_level);

	/* For sdp we don't need the link key. */
	if (sec_level == BT_SECURITY_SDP)
		return 1;

	/* For non 2.1 devices and low security level we don't need the link
	   key. */
	if (sec_level == BT_SECURITY_LOW && !hci_conn_ssp_enabled(conn))
		return 1;

	/* For other security levels we need the link key. */
	if (!test_bit(HCI_CONN_AUTH, &conn->flags))
		goto auth;

	/* An authenticated FIPS approved combination key has sufficient
	 * security for security level 4. */
	if (conn->key_type == HCI_LK_AUTH_COMBINATION_P256 &&
	    sec_level == BT_SECURITY_FIPS)
		goto encrypt;

	/* An authenticated combination key has sufficient security for
	   security level 3. */
	if ((conn->key_type == HCI_LK_AUTH_COMBINATION_P192 ||
	     conn->key_type == HCI_LK_AUTH_COMBINATION_P256) &&
	    sec_level == BT_SECURITY_HIGH)
		goto encrypt;

	/* An unauthenticated combination key has sufficient security for
	   security level 1 and 2. */
	if ((conn->key_type == HCI_LK_UNAUTH_COMBINATION_P192 ||
	     conn->key_type == HCI_LK_UNAUTH_COMBINATION_P256) &&
	    (sec_level == BT_SECURITY_MEDIUM || sec_level == BT_SECURITY_LOW))
		goto encrypt;

	/* A combination key has always sufficient security for the security
	   levels 1 or 2. High security level requires the combination key
	   is generated using maximum PIN code length (16).
	   For pre 2.1 units. */
	if (conn->key_type == HCI_LK_COMBINATION &&
	    (sec_level == BT_SECURITY_MEDIUM || sec_level == BT_SECURITY_LOW ||
	     conn->pin_length == 16))
		goto encrypt;

auth:
	if (test_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags))
		return 0;

	if (initiator)
		set_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags);

	if (!hci_conn_auth(conn, sec_level, auth_type))
		return 0;

encrypt:
	if (test_bit(HCI_CONN_ENCRYPT, &conn->flags)) {
		/* Ensure that the encryption key size has been read,
		 * otherwise stall the upper layer responses.
		 */
		if (!conn->enc_key_size)
			return 0;

		/* Nothing else needed, all requirements are met */
		return 1;
	}

	hci_conn_encrypt(conn);
	return 0;
}