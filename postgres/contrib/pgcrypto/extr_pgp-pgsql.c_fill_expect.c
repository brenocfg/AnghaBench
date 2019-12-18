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
struct debug_expect {int cipher_algo; int s2k_mode; int s2k_count; int s2k_cipher_algo; int s2k_digest_algo; int compress_algo; int use_sess_key; int disable_mdc; int unicode_mode; scalar_t__ expect; scalar_t__ debug; } ;

/* Variables and functions */

__attribute__((used)) static void
fill_expect(struct debug_expect *ex, int text_mode)
{
	ex->debug = 0;
	ex->expect = 0;
	ex->cipher_algo = -1;
	ex->s2k_mode = -1;
	ex->s2k_count = -1;
	ex->s2k_cipher_algo = -1;
	ex->s2k_digest_algo = -1;
	ex->compress_algo = -1;
	ex->use_sess_key = -1;
	ex->disable_mdc = -1;
	ex->unicode_mode = -1;
}