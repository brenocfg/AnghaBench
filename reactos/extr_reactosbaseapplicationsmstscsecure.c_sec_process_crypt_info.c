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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  modulus ;
typedef  int /*<<< orphan*/  exponent ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int SEC_EXPONENT_SIZE ; 
 int SEC_MAX_MODULUS_SIZE ; 
 int /*<<< orphan*/  SEC_RANDOM_SIZE ; 
 int /*<<< orphan*/  g_client_random ; 
 int /*<<< orphan*/  g_sec_crypted_random ; 
 int /*<<< orphan*/  g_server_public_key_len ; 
 int /*<<< orphan*/  generate_random (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_generate_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_parse_crypt_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_rsa_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sec_process_crypt_info(STREAM s)
{
	uint8 *server_random = NULL;
	uint8 modulus[SEC_MAX_MODULUS_SIZE];
	uint8 exponent[SEC_EXPONENT_SIZE];
	uint32 rc4_key_size;

	memset(modulus, 0, sizeof(modulus));
	memset(exponent, 0, sizeof(exponent));
	if (!sec_parse_crypt_info(s, &rc4_key_size, &server_random, modulus, exponent))
	{
		DEBUG(("Failed to parse crypt info\n"));
		return;
	}
	DEBUG(("Generating client random\n"));
	generate_random(g_client_random);
	sec_rsa_encrypt(g_sec_crypted_random, g_client_random, SEC_RANDOM_SIZE,
			g_server_public_key_len, modulus, exponent);
	sec_generate_keys(g_client_random, server_random, rc4_key_size);
}