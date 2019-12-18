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
struct debug_expect {int expect; void* unicode_mode; void* compress_algo; void* s2k_cipher_algo; int /*<<< orphan*/  s2k_digest_algo; void* s2k_count; void* s2k_mode; void* use_sess_key; void* disable_mdc; void* cipher_algo; void* debug; } ;
typedef  int /*<<< orphan*/  PGP_Context ;

/* Variables and functions */
 int PXE_ARGUMENT_ERROR ; 
 void* atoi (char*) ; 
 int pgp_disable_mdc (int /*<<< orphan*/ *,void*) ; 
 void* pgp_get_cipher_code (char*) ; 
 int /*<<< orphan*/  pgp_get_digest_code (char*) ; 
 int pgp_set_cipher_algo (int /*<<< orphan*/ *,char*) ; 
 int pgp_set_compress_algo (int /*<<< orphan*/ *,void*) ; 
 int pgp_set_compress_level (int /*<<< orphan*/ *,void*) ; 
 int pgp_set_convert_crlf (int /*<<< orphan*/ *,void*) ; 
 int pgp_set_s2k_cipher_algo (int /*<<< orphan*/ *,char*) ; 
 int pgp_set_s2k_count (int /*<<< orphan*/ *,void*) ; 
 int pgp_set_s2k_digest_algo (int /*<<< orphan*/ *,char*) ; 
 int pgp_set_s2k_mode (int /*<<< orphan*/ *,void*) ; 
 int pgp_set_sess_key (int /*<<< orphan*/ *,void*) ; 
 int pgp_set_unicode_mode (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
set_arg(PGP_Context *ctx, char *key, char *val,
		struct debug_expect *ex)
{
	int			res = 0;

	if (strcmp(key, "cipher-algo") == 0)
		res = pgp_set_cipher_algo(ctx, val);
	else if (strcmp(key, "disable-mdc") == 0)
		res = pgp_disable_mdc(ctx, atoi(val));
	else if (strcmp(key, "sess-key") == 0)
		res = pgp_set_sess_key(ctx, atoi(val));
	else if (strcmp(key, "s2k-mode") == 0)
		res = pgp_set_s2k_mode(ctx, atoi(val));
	else if (strcmp(key, "s2k-count") == 0)
		res = pgp_set_s2k_count(ctx, atoi(val));
	else if (strcmp(key, "s2k-digest-algo") == 0)
		res = pgp_set_s2k_digest_algo(ctx, val);
	else if (strcmp(key, "s2k-cipher-algo") == 0)
		res = pgp_set_s2k_cipher_algo(ctx, val);
	else if (strcmp(key, "compress-algo") == 0)
		res = pgp_set_compress_algo(ctx, atoi(val));
	else if (strcmp(key, "compress-level") == 0)
		res = pgp_set_compress_level(ctx, atoi(val));
	else if (strcmp(key, "convert-crlf") == 0)
		res = pgp_set_convert_crlf(ctx, atoi(val));
	else if (strcmp(key, "unicode-mode") == 0)
		res = pgp_set_unicode_mode(ctx, atoi(val));

	/*
	 * The remaining options are for debugging/testing and are therefore not
	 * documented in the user-facing docs.
	 */
	else if (ex != NULL && strcmp(key, "debug") == 0)
		ex->debug = atoi(val);
	else if (ex != NULL && strcmp(key, "expect-cipher-algo") == 0)
	{
		ex->expect = 1;
		ex->cipher_algo = pgp_get_cipher_code(val);
	}
	else if (ex != NULL && strcmp(key, "expect-disable-mdc") == 0)
	{
		ex->expect = 1;
		ex->disable_mdc = atoi(val);
	}
	else if (ex != NULL && strcmp(key, "expect-sess-key") == 0)
	{
		ex->expect = 1;
		ex->use_sess_key = atoi(val);
	}
	else if (ex != NULL && strcmp(key, "expect-s2k-mode") == 0)
	{
		ex->expect = 1;
		ex->s2k_mode = atoi(val);
	}
	else if (ex != NULL && strcmp(key, "expect-s2k-count") == 0)
	{
		ex->expect = 1;
		ex->s2k_count = atoi(val);
	}
	else if (ex != NULL && strcmp(key, "expect-s2k-digest-algo") == 0)
	{
		ex->expect = 1;
		ex->s2k_digest_algo = pgp_get_digest_code(val);
	}
	else if (ex != NULL && strcmp(key, "expect-s2k-cipher-algo") == 0)
	{
		ex->expect = 1;
		ex->s2k_cipher_algo = pgp_get_cipher_code(val);
	}
	else if (ex != NULL && strcmp(key, "expect-compress-algo") == 0)
	{
		ex->expect = 1;
		ex->compress_algo = atoi(val);
	}
	else if (ex != NULL && strcmp(key, "expect-unicode-mode") == 0)
	{
		ex->expect = 1;
		ex->unicode_mode = atoi(val);
	}
	else
		res = PXE_ARGUMENT_ERROR;

	return res;
}