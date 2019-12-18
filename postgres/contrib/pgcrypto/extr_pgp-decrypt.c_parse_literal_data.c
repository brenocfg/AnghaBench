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
typedef  int /*<<< orphan*/  const uint8 ;
struct TYPE_3__ {int unexpected_binary; int unicode_mode; scalar_t__ convert_crlf; scalar_t__ text_mode; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_Context ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int /*<<< orphan*/  GETBYTE (int /*<<< orphan*/ *,int) ; 
 int PXE_PGP_CORRUPT_DATA ; 
 int copy_crlf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int*) ; 
 int mbuf_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int pullf_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int pullf_read_max (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  px_debug (char*,...) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
parse_literal_data(PGP_Context *ctx, MBuf *dst, PullFilter *pkt)
{
	int			type;
	int			name_len;
	int			res;
	uint8	   *buf;
	uint8		tmpbuf[4];
	int			got_cr = 0;

	GETBYTE(pkt, type);
	GETBYTE(pkt, name_len);

	/* skip name */
	while (name_len > 0)
	{
		res = pullf_read(pkt, name_len, &buf);
		if (res < 0)
			return res;
		if (res == 0)
			break;
		name_len -= res;
	}
	if (name_len > 0)
	{
		px_debug("parse_literal_data: unexpected eof");
		return PXE_PGP_CORRUPT_DATA;
	}

	/* skip date */
	res = pullf_read_max(pkt, 4, &buf, tmpbuf);
	if (res != 4)
	{
		px_debug("parse_literal_data: unexpected eof");
		return PXE_PGP_CORRUPT_DATA;
	}
	px_memset(tmpbuf, 0, 4);

	/*
	 * If called from an SQL function that returns text, pgp_decrypt() rejects
	 * inputs not self-identifying as text.
	 */
	if (ctx->text_mode)
		if (type != 't' && type != 'u')
		{
			px_debug("parse_literal_data: data type=%c", type);
			ctx->unexpected_binary = true;
		}

	ctx->unicode_mode = (type == 'u') ? 1 : 0;

	/* read data */
	while (1)
	{
		res = pullf_read(pkt, 32 * 1024, &buf);
		if (res <= 0)
			break;

		if (ctx->text_mode && ctx->convert_crlf)
			res = copy_crlf(dst, buf, res, &got_cr);
		else
			res = mbuf_append(dst, buf, res);
		if (res < 0)
			break;
	}
	if (res >= 0 && got_cr)
		res = mbuf_append(dst, (const uint8 *) "\r", 1);
	return res;
}