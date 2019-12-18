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
typedef  int /*<<< orphan*/  null_data ;
typedef  int /*<<< orphan*/  hwid ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int LICENCE_HWID_SIZE ; 
 int LICENCE_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  LICENCE_TAG_LICENCE_INFO ; 
 int /*<<< orphan*/  LICENCE_TAG_NEW_LICENCE_REQUEST ; 
 int SEC_MODULUS_SIZE ; 
 int /*<<< orphan*/  SEC_RANDOM_SIZE ; 
 int /*<<< orphan*/  g_hostname ; 
 scalar_t__ g_licence_key ; 
 int /*<<< orphan*/  g_licence_sign_key ; 
 int /*<<< orphan*/  g_username ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_generate_hwid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_generate_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_send_new_licence_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int load_licence (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdssl_rc4_crypt (void*,char*,char*,int) ; 
 void* rdssl_rc4_info_create () ; 
 int /*<<< orphan*/  rdssl_rc4_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_rc4_set_key (void*,char*,int) ; 
 int /*<<< orphan*/  sec_sign (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
licence_process_request(STREAM s)
{
	uint8 null_data[SEC_MODULUS_SIZE];
	uint8 *server_random;
	uint8 signature[LICENCE_SIGNATURE_SIZE];
	uint8 hwid[LICENCE_HWID_SIZE];
	uint8 *licence_data;
	int licence_size;
	void * crypt_key;

	/* Retrieve the server random from the incoming packet */
	in_uint8p(s, server_random, SEC_RANDOM_SIZE);

	/* We currently use null client keys. This is a bit naughty but, hey,
	   the security of licence negotiation isn't exactly paramount. */
	memset(null_data, 0, sizeof(null_data));
	licence_generate_keys(null_data, server_random, null_data);

	licence_size = load_licence(&licence_data);
	if (licence_size > 0)
	{
		/* Generate a signature for the HWID buffer */
		licence_generate_hwid(hwid);
		sec_sign(signature, 16, g_licence_sign_key, 16, hwid, sizeof(hwid));

		/* Now encrypt the HWID */
		crypt_key = rdssl_rc4_info_create();
		rdssl_rc4_set_key(crypt_key, (char *)g_licence_key, 16);
		rdssl_rc4_crypt(crypt_key, (char *)hwid, (char *)hwid, sizeof(hwid));
		rdssl_rc4_info_delete(crypt_key);

#if WITH_DEBUG
		DEBUG(("Sending licensing PDU (message type 0x%02x)\n", LICENCE_TAG_LICENCE_INFO));
#endif
		licence_info(null_data, null_data, licence_data, licence_size, hwid, signature);

		xfree(licence_data);
		return;
	}

#if WITH_DEBUG
	DEBUG(("Sending licensing PDU (message type 0x%02x)\n", LICENCE_TAG_NEW_LICENCE_REQUEST));
#endif
	licence_send_new_licence_request(null_data, null_data, g_username, g_hostname);
}