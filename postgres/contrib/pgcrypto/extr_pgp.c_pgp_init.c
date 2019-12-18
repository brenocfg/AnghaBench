#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  text_mode; int /*<<< orphan*/  convert_crlf; int /*<<< orphan*/  unicode_mode; int /*<<< orphan*/  use_sess_key; int /*<<< orphan*/  disable_mdc; int /*<<< orphan*/  compress_level; int /*<<< orphan*/  compress_algo; int /*<<< orphan*/  s2k_digest_algo; int /*<<< orphan*/  s2k_count; int /*<<< orphan*/  s2k_mode; int /*<<< orphan*/  s2k_cipher_algo; int /*<<< orphan*/  cipher_algo; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int /*<<< orphan*/  def_cipher_algo ; 
 int /*<<< orphan*/  def_compress_algo ; 
 int /*<<< orphan*/  def_compress_level ; 
 int /*<<< orphan*/  def_convert_crlf ; 
 int /*<<< orphan*/  def_disable_mdc ; 
 int /*<<< orphan*/  def_s2k_cipher_algo ; 
 int /*<<< orphan*/  def_s2k_count ; 
 int /*<<< orphan*/  def_s2k_digest_algo ; 
 int /*<<< orphan*/  def_s2k_mode ; 
 int /*<<< orphan*/  def_text_mode ; 
 int /*<<< orphan*/  def_unicode_mode ; 
 int /*<<< orphan*/  def_use_sess_key ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* px_alloc (int) ; 

int
pgp_init(PGP_Context **ctx_p)
{
	PGP_Context *ctx;

	ctx = px_alloc(sizeof *ctx);
	memset(ctx, 0, sizeof *ctx);

	ctx->cipher_algo = def_cipher_algo;
	ctx->s2k_cipher_algo = def_s2k_cipher_algo;
	ctx->s2k_mode = def_s2k_mode;
	ctx->s2k_count = def_s2k_count;
	ctx->s2k_digest_algo = def_s2k_digest_algo;
	ctx->compress_algo = def_compress_algo;
	ctx->compress_level = def_compress_level;
	ctx->disable_mdc = def_disable_mdc;
	ctx->use_sess_key = def_use_sess_key;
	ctx->unicode_mode = def_unicode_mode;
	ctx->convert_crlf = def_convert_crlf;
	ctx->text_mode = def_text_mode;

	*ctx_p = ctx;
	return 0;
}