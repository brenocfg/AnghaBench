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
struct debug_expect {int dummy; } ;
struct TYPE_3__ {scalar_t__ use_sess_key; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int /*<<< orphan*/  EX_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipher_algo ; 
 int /*<<< orphan*/  compress_algo ; 
 int /*<<< orphan*/  disable_mdc ; 
 int /*<<< orphan*/  s2k_cipher_algo ; 
 int /*<<< orphan*/  s2k_count ; 
 int /*<<< orphan*/  s2k_digest_algo ; 
 int /*<<< orphan*/  s2k_mode ; 
 int /*<<< orphan*/  unicode_mode ; 
 int /*<<< orphan*/  use_sess_key ; 

__attribute__((used)) static void
check_expect(PGP_Context *ctx, struct debug_expect *ex)
{
	EX_CHECK(cipher_algo);
	EX_CHECK(s2k_mode);
	EX_CHECK(s2k_count);
	EX_CHECK(s2k_digest_algo);
	EX_CHECK(use_sess_key);
	if (ctx->use_sess_key)
		EX_CHECK(s2k_cipher_algo);
	EX_CHECK(disable_mdc);
	EX_CHECK(compress_algo);
	EX_CHECK(unicode_mode);
}