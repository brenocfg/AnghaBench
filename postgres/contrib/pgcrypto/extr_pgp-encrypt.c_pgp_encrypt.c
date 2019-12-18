#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_12__ {scalar_t__ disable_mdc; scalar_t__ compress_algo; scalar_t__ compress_level; scalar_t__ convert_crlf; scalar_t__ text_mode; scalar_t__ pub_key; scalar_t__ sym_key; } ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  TYPE_1__ PGP_Context ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int PXE_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  crlf_filter ; 
 int /*<<< orphan*/  encrypt_filter ; 
 int init_compress (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int init_encdata_packet (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int init_litdata_packet (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int init_s2k_key (TYPE_1__*) ; 
 int init_sess_key (TYPE_1__*) ; 
 int /*<<< orphan*/  mbuf_avail (int /*<<< orphan*/ *) ; 
 int mbuf_grab (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mdc_filter ; 
 int pgp_write_pubenc_sesskey (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pushf_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pushf_create_mbuf_writer (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int pushf_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushf_free_all (int /*<<< orphan*/ *) ; 
 int pushf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int write_prefix (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int write_symenc_sesskey (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
pgp_encrypt(PGP_Context *ctx, MBuf *src, MBuf *dst)
{
	int			res;
	int			len;
	uint8	   *buf;
	PushFilter *pf,
			   *pf_tmp;

	/*
	 * do we have any key
	 */
	if (!ctx->sym_key && !ctx->pub_key)
		return PXE_ARGUMENT_ERROR;

	/* MBuf writer */
	res = pushf_create_mbuf_writer(&pf, dst);
	if (res < 0)
		goto out;

	/*
	 * initialize sym_key
	 */
	if (ctx->sym_key)
	{
		res = init_s2k_key(ctx);
		if (res < 0)
			goto out;
	}

	res = init_sess_key(ctx);
	if (res < 0)
		goto out;

	/*
	 * write keypkt
	 */
	if (ctx->pub_key)
		res = pgp_write_pubenc_sesskey(ctx, pf);
	else
		res = write_symenc_sesskey(ctx, pf);
	if (res < 0)
		goto out;

	/* encrypted data pkt */
	res = init_encdata_packet(&pf_tmp, ctx, pf);
	if (res < 0)
		goto out;
	pf = pf_tmp;

	/* encrypter */
	res = pushf_create(&pf_tmp, &encrypt_filter, ctx, pf);
	if (res < 0)
		goto out;
	pf = pf_tmp;

	/* hasher */
	if (ctx->disable_mdc == 0)
	{
		res = pushf_create(&pf_tmp, &mdc_filter, ctx, pf);
		if (res < 0)
			goto out;
		pf = pf_tmp;
	}

	/* prefix */
	res = write_prefix(ctx, pf);
	if (res < 0)
		goto out;

	/* compressor */
	if (ctx->compress_algo > 0 && ctx->compress_level > 0)
	{
		res = init_compress(&pf_tmp, ctx, pf);
		if (res < 0)
			goto out;
		pf = pf_tmp;
	}

	/* data streamer */
	res = init_litdata_packet(&pf_tmp, ctx, pf);
	if (res < 0)
		goto out;
	pf = pf_tmp;


	/* text conversion? */
	if (ctx->text_mode && ctx->convert_crlf)
	{
		res = pushf_create(&pf_tmp, &crlf_filter, ctx, pf);
		if (res < 0)
			goto out;
		pf = pf_tmp;
	}

	/*
	 * chain complete
	 */

	len = mbuf_grab(src, mbuf_avail(src), &buf);
	res = pushf_write(pf, buf, len);
	if (res >= 0)
		res = pushf_flush(pf);
out:
	pushf_free_all(pf);
	return res;
}