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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  sealed_buffer ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int LICENCE_HWID_SIZE ; 
 int LICENCE_SIGNATURE_SIZE ; 
 int LICENCE_TOKEN_SIZE ; 
 scalar_t__ g_licence_key ; 
 int /*<<< orphan*/  g_licence_sign_key ; 
 int /*<<< orphan*/  licence_generate_hwid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_parse_platform_challenge (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  licence_send_platform_challenge_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rdssl_rc4_crypt (void*,char*,char*,int) ; 
 void* rdssl_rc4_info_create () ; 
 int /*<<< orphan*/  rdssl_rc4_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_rc4_set_key (void*,char*,int) ; 
 int /*<<< orphan*/  sec_sign (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
licence_process_platform_challenge(STREAM s)
{
	uint8 *in_token = NULL, *in_sig;
	uint8 out_token[LICENCE_TOKEN_SIZE], decrypt_token[LICENCE_TOKEN_SIZE];
	uint8 hwid[LICENCE_HWID_SIZE], crypt_hwid[LICENCE_HWID_SIZE];
	uint8 sealed_buffer[LICENCE_TOKEN_SIZE + LICENCE_HWID_SIZE];
	uint8 out_sig[LICENCE_SIGNATURE_SIZE];
	void * crypt_key;

	/* Parse incoming packet and save the encrypted token */
	licence_parse_platform_challenge(s, &in_token, &in_sig);
	memcpy(out_token, in_token, LICENCE_TOKEN_SIZE);

	/* Decrypt the token. It should read TEST in Unicode. */
	crypt_key = rdssl_rc4_info_create();
	rdssl_rc4_set_key(crypt_key, (char *)g_licence_key, 16);
	rdssl_rc4_crypt(crypt_key, (char *)in_token, (char *)decrypt_token, LICENCE_TOKEN_SIZE);
	rdssl_rc4_info_delete(crypt_key);
	
	/* Generate a signature for a buffer of token and HWID */
	licence_generate_hwid(hwid);
	memcpy(sealed_buffer, decrypt_token, LICENCE_TOKEN_SIZE);
	memcpy(sealed_buffer + LICENCE_TOKEN_SIZE, hwid, LICENCE_HWID_SIZE);
	sec_sign(out_sig, 16, g_licence_sign_key, 16, sealed_buffer, sizeof(sealed_buffer));

	/* Now encrypt the HWID */
	crypt_key = rdssl_rc4_info_create();
	rdssl_rc4_set_key(crypt_key, (char *)g_licence_key, 16);
	rdssl_rc4_crypt(crypt_key, (char *)hwid, (char *)crypt_hwid, LICENCE_HWID_SIZE);

	licence_send_platform_challenge_response(out_token, crypt_hwid, out_sig);
}