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
struct debug_expect {scalar_t__ expect; } ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  PGP_Context ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 scalar_t__ VARSIZE_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_expect (int /*<<< orphan*/ *,struct debug_expect*) ; 
 int /*<<< orphan*/  clear_and_pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_from_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_mbuf_from_vardata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_work (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,struct debug_expect*) ; 
 int /*<<< orphan*/  mbuf_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mbuf_create (scalar_t__) ; 
 int /*<<< orphan*/ * mbuf_create_from_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbuf_free (int /*<<< orphan*/ *) ; 
 int mbuf_steal_data (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int pgp_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgp_free (int /*<<< orphan*/ *) ; 
 int pgp_get_unicode_mode (int /*<<< orphan*/ *) ; 
 int pgp_set_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int pgp_set_symkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  px_THROW_ERROR (int) ; 
 int /*<<< orphan*/  px_set_debug_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bytea *
decrypt_internal(int is_pubenc, int need_text, text *data,
				 text *key, text *keypsw, text *args)
{
	int			err;
	MBuf	   *src = NULL,
			   *dst = NULL;
	uint8		tmp[VARHDRSZ];
	uint8	   *restmp;
	bytea	   *res;
	int			res_len;
	PGP_Context *ctx = NULL;
	struct debug_expect ex;
	int			got_unicode = 0;


	init_work(&ctx, need_text, args, &ex);

	src = mbuf_create_from_data((uint8 *) VARDATA_ANY(data),
								VARSIZE_ANY_EXHDR(data));
	dst = mbuf_create(VARSIZE_ANY(data) + 2048);

	/*
	 * reserve room for header
	 */
	mbuf_append(dst, tmp, VARHDRSZ);

	/*
	 * set key
	 */
	if (is_pubenc)
	{
		uint8	   *psw = NULL;
		int			psw_len = 0;
		MBuf	   *kbuf;

		if (keypsw)
		{
			psw = (uint8 *) VARDATA_ANY(keypsw);
			psw_len = VARSIZE_ANY_EXHDR(keypsw);
		}
		kbuf = create_mbuf_from_vardata(key);
		err = pgp_set_pubkey(ctx, kbuf, psw, psw_len, 1);
		mbuf_free(kbuf);
	}
	else
		err = pgp_set_symkey(ctx, (uint8 *) VARDATA_ANY(key),
							 VARSIZE_ANY_EXHDR(key));

	/* decrypt */
	if (err >= 0)
	{
		err = pgp_decrypt(ctx, src, dst);

		if (ex.expect)
			check_expect(ctx, &ex);

		/* remember the setting */
		got_unicode = pgp_get_unicode_mode(ctx);
	}

	mbuf_free(src);
	pgp_free(ctx);

	if (err)
	{
		px_set_debug_handler(NULL);
		mbuf_free(dst);
		px_THROW_ERROR(err);
	}

	res_len = mbuf_steal_data(dst, &restmp);
	mbuf_free(dst);

	/* res_len includes VARHDRSZ */
	res = (bytea *) restmp;
	SET_VARSIZE(res, res_len);

	if (need_text && got_unicode)
	{
		text	   *utf = convert_from_utf8(res);

		if (utf != res)
		{
			clear_and_pfree(res);
			res = utf;
		}
	}
	px_set_debug_handler(NULL);

	return res;
}