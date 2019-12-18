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
typedef  char uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int BB_CLIENT_MACHINE_NAME_BLOB ; 
 int BB_CLIENT_USER_NAME_BLOB ; 
 int LICENCE_TAG_NEW_LICENCE_REQUEST ; 
 scalar_t__ RDP_V5 ; 
 int /*<<< orphan*/  SEC_LICENSE_PKT ; 
 int SEC_MODULUS_SIZE ; 
 int SEC_PADDING_SIZE ; 
 int SEC_RANDOM_SIZE ; 
 scalar_t__ g_rdp_version ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
licence_send_new_licence_request(uint8 * client_random, uint8 * rsa_data, char *user, char *host)
{
	uint32 sec_flags = SEC_LICENSE_PKT;
	uint16 userlen = strlen(user) + 1;
	uint16 hostlen = strlen(host) + 1;
	uint16 length =
		24 + SEC_RANDOM_SIZE + SEC_MODULUS_SIZE + SEC_PADDING_SIZE + userlen + hostlen;
	STREAM s;

	s = sec_init(sec_flags, length + 2);

	out_uint8(s, LICENCE_TAG_NEW_LICENCE_REQUEST);
	out_uint8(s, ((g_rdp_version >= RDP_V5) ? 3 : 2));	/* version */
	out_uint16_le(s, length);

	out_uint32_le(s, 1);	// KEY_EXCHANGE_ALG_RSA
	out_uint16(s, 0);
	out_uint16_le(s, 0xff01);

	out_uint8p(s, client_random, SEC_RANDOM_SIZE);
	out_uint16_le(s, 2);
	out_uint16_le(s, (SEC_MODULUS_SIZE + SEC_PADDING_SIZE));
	out_uint8p(s, rsa_data, SEC_MODULUS_SIZE);
	out_uint8s(s, SEC_PADDING_SIZE);

	/* Username LICENSE_BINARY_BLOB */
	out_uint16_le(s, BB_CLIENT_USER_NAME_BLOB);
	out_uint16_le(s, userlen);
	out_uint8p(s, user, userlen);

	/* Machinename LICENSE_BINARY_BLOB */
	out_uint16_le(s, BB_CLIENT_MACHINE_NAME_BLOB);
	out_uint16_le(s, hostlen);
	out_uint8p(s, host, hostlen);

	s_mark_end(s);
	sec_send(s, sec_flags);
}