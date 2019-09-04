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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/ * ENGINE_by_id (char*) ; 
 int /*<<< orphan*/  ENGINE_ctrl_cmd_string (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_load_builtin_engines () ; 
 int /*<<< orphan*/ * ENGINE_load_private_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (int,char*,...) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_openssl_errors () ; 
 scalar_t__ key_pass ; 
 int /*<<< orphan*/  pem_pw_cb ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static EVP_PKEY *read_private_key(const char *private_key_name)
{
	EVP_PKEY *private_key;

	if (!strncmp(private_key_name, "pkcs11:", 7)) {
		ENGINE *e;

		ENGINE_load_builtin_engines();
		drain_openssl_errors();
		e = ENGINE_by_id("pkcs11");
		ERR(!e, "Load PKCS#11 ENGINE");
		if (ENGINE_init(e))
			drain_openssl_errors();
		else
			ERR(1, "ENGINE_init");
		if (key_pass)
			ERR(!ENGINE_ctrl_cmd_string(e, "PIN", key_pass, 0),
			    "Set PKCS#11 PIN");
		private_key = ENGINE_load_private_key(e, private_key_name,
						      NULL, NULL);
		ERR(!private_key, "%s", private_key_name);
	} else {
		BIO *b;

		b = BIO_new_file(private_key_name, "rb");
		ERR(!b, "%s", private_key_name);
		private_key = PEM_read_bio_PrivateKey(b, NULL, pem_pw_cb,
						      NULL);
		ERR(!private_key, "%s", private_key_name);
		BIO_free(b);
	}

	return private_key;
}