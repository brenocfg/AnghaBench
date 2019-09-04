#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  io; int /*<<< orphan*/  blocksize; scalar_t__ block; } ;
typedef  int /*<<< orphan*/  RCrypto ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  r_crypto_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_crypto_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_crypto_get_output (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * r_crypto_new () ; 
 int /*<<< orphan*/  r_crypto_set_iv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_crypto_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_crypto_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ r_crypto_use (int /*<<< orphan*/ *,char const*) ; 
 int r_hex_str2bin (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_write_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool encrypt_or_decrypt_block(RCore *core, const char *algo, const char *key, int direction, const char *iv) {
	//TODO: generalise no_key_mode for all non key encoding/decoding.
	int keylen = 0;
	bool no_key_mode = !strcmp ("base64", algo) || !strcmp ("base91", algo) || !strcmp ("punycode", algo);
	ut8 *binkey = NULL;
	if (!strncmp (key, "s:", 2)) {
		binkey = (ut8*)strdup (key + 2);
		keylen = strlen (key + 2);
	} else {
		binkey = (ut8 *)strdup (key);
		keylen = r_hex_str2bin (key, binkey);
	}
	if (!no_key_mode && keylen < 1) {
		eprintf ("%s key not defined. Use -S [key]\n", ((!direction) ? "Encryption" : "Decryption"));
		return false;
	}
	RCrypto *cry = r_crypto_new ();
	if (r_crypto_use (cry, algo)) {
		if (!binkey) {
			eprintf ("Cannot allocate %d byte(s)\n", keylen);
			r_crypto_free (cry);
			return false;
		}
		if (r_crypto_set_key (cry, binkey, keylen, 0, direction)) {
			if (iv) {
				ut8 *biniv = malloc (strlen (iv) + 1);
				int ivlen = r_hex_str2bin (iv, biniv);
				if (ivlen < 1) {
					ivlen = strlen(iv);
					strcpy ((char *)biniv, iv);
				}
				if (!r_crypto_set_iv (cry, biniv, ivlen)) {
					eprintf ("Invalid IV.\n");
					return 0;
				}
			}
			r_crypto_update (cry, (const ut8*)core->block, core->blocksize);
			r_crypto_final (cry, NULL, 0);

			int result_size = 0;
			ut8 *result = r_crypto_get_output (cry, &result_size);
			if (result) {
				r_io_write_at (core->io, core->offset, result, result_size);
				eprintf ("Written %d byte(s)\n", result_size);
				free (result);
			}
		} else {
			eprintf ("Invalid key\n");
		}
		free (binkey);
		r_crypto_free (cry);
		return 0;
	} else {
		eprintf ("Unknown %s algorithm '%s'\n", ((!direction) ? "encryption" : "decryption") ,algo);
	}
	r_crypto_free (cry);
	return 1;
}