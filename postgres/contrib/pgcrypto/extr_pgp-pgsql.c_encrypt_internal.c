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
typedef  int /*<<< orphan*/  text ;
struct debug_expect {scalar_t__ debug; } ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  PGP_Context ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 scalar_t__ VARSIZE_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_and_pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_to_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_mbuf_from_vardata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_work (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,struct debug_expect*) ; 
 int /*<<< orphan*/  mbuf_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mbuf_create (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_free (int /*<<< orphan*/ *) ; 
 int mbuf_steal_data (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int pgp_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgp_free (int /*<<< orphan*/ *) ; 
 scalar_t__ pgp_get_unicode_mode (int /*<<< orphan*/ *) ; 
 int pgp_set_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pgp_set_symkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_THROW_ERROR (int) ; 
 int /*<<< orphan*/  px_set_debug_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bytea *
encrypt_internal(int is_pubenc, int is_text,
				 text *data, text *key, text *args)
{
	MBuf	   *src,
			   *dst;
	uint8		tmp[VARHDRSZ];
	uint8	   *restmp;
	bytea	   *res;
	int			res_len;
	PGP_Context *ctx;
	int			err;
	struct debug_expect ex;
	text	   *tmp_data = NULL;

	init_work(&ctx, is_text, args, &ex);

	if (is_text && pgp_get_unicode_mode(ctx))
	{
		tmp_data = convert_to_utf8(data);
		if (tmp_data == data)
			tmp_data = NULL;
		else
			data = tmp_data;
	}

	src = create_mbuf_from_vardata(data);
	dst = mbuf_create(VARSIZE_ANY(data) + 128);

	/*
	 * reserve room for header
	 */
	mbuf_append(dst, tmp, VARHDRSZ);

	/*
	 * set key
	 */
	if (is_pubenc)
	{
		MBuf	   *kbuf = create_mbuf_from_vardata(key);

		err = pgp_set_pubkey(ctx, kbuf,
							 NULL, 0, 0);
		mbuf_free(kbuf);
	}
	else
		err = pgp_set_symkey(ctx, (uint8 *) VARDATA_ANY(key),
							 VARSIZE_ANY_EXHDR(key));

	/*
	 * encrypt
	 */
	if (err >= 0)
		err = pgp_encrypt(ctx, src, dst);

	/*
	 * check for error
	 */
	if (err)
	{
		if (ex.debug)
			px_set_debug_handler(NULL);
		if (tmp_data)
			clear_and_pfree(tmp_data);
		pgp_free(ctx);
		mbuf_free(src);
		mbuf_free(dst);
		px_THROW_ERROR(err);
	}

	/* res_len includes VARHDRSZ */
	res_len = mbuf_steal_data(dst, &restmp);
	res = (bytea *) restmp;
	SET_VARSIZE(res, res_len);

	if (tmp_data)
		clear_and_pfree(tmp_data);
	pgp_free(ctx);
	mbuf_free(src);
	mbuf_free(dst);

	px_set_debug_handler(NULL);

	return res;
}