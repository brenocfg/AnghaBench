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

/* Variables and functions */
 int /*<<< orphan*/  g_licence_key ; 
 int /*<<< orphan*/  g_licence_sign_key ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sec_hash_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_hash_48 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void
licence_generate_keys(uint8 * client_random, uint8 * server_random, uint8 * pre_master_secret)
{
	uint8 master_secret[48];
	uint8 key_block[48];

	/* Generate master secret and then key material */
	sec_hash_48(master_secret, pre_master_secret, client_random, server_random, 'A');
	sec_hash_48(key_block, master_secret, server_random, client_random, 'A');

	/* Store first 16 bytes of session key as MAC secret */
	memcpy(g_licence_sign_key, key_block, 16);

	/* Generate RC4 key from next 16 bytes */
	sec_hash_16(g_licence_key, &key_block[16], client_random, server_random);
}