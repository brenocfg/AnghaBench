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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  RCrypto ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_crypto_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_crypto_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_crypto_get_output (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * r_crypto_new () ; 
 int /*<<< orphan*/  r_crypto_set_iv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ r_crypto_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_crypto_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_crypto_use (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ r_file_slurp (char*,int*) ; 
 scalar_t__ r_stdin_slurp (int*) ; 
 TYPE_1__ s ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int encrypt_or_decrypt_file(const char *algo, int direction, char *filename, const ut8 *iv, int ivlen, int mode) {
	bool no_key_mode = !strcmp ("base64", algo) || !strcmp ("base91", algo) || !strcmp ("punycode", algo); // TODO: generalise this for all non key encoding/decoding.
	if (no_key_mode || s.len > 0) {
		RCrypto *cry = r_crypto_new ();
		if (r_crypto_use (cry, algo)) {
			if (r_crypto_set_key (cry, s.buf, s.len, 0, direction)) {
				int file_size;
				ut8 *buf = strcmp (filename, "-")
				           ? (ut8 *) r_file_slurp (filename, &file_size)
					   : (ut8 *) r_stdin_slurp (&file_size);
				if (!buf) {
					eprintf ("rahash2: Cannot open '%s'\n", filename);
					return -1;
				}

				if (iv && !r_crypto_set_iv (cry, iv, ivlen)) {
					eprintf ("Invalid IV.\n");
					free (buf);
					return 0;
				}

				r_crypto_update (cry, buf, file_size);
				r_crypto_final (cry, NULL, 0);

				int result_size = 0;
				ut8 *result = r_crypto_get_output (cry, &result_size);
				if (result) {
					write (1, result, result_size);
					free (result);
				}
				free (buf);
			} else {
				eprintf ("Invalid key\n");
			}
			return 0;
		} else {
			eprintf ("Unknown %s algorithm '%s'\n", ((!direction)? "encryption": "decryption"), algo);
		}
		r_crypto_free (cry);
	} else {
		eprintf ("%s key not defined. Use -S [key]\n", ((!direction)? "Encryption": "Decryption"));
	}
	return 1;
}