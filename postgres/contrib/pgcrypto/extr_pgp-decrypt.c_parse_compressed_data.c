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
typedef  int uint8 ;
struct TYPE_5__ {int compress_algo; int unsupported_compr; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_Context ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int /*<<< orphan*/  GETBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NO_COMPR ; 
 int /*<<< orphan*/  NO_MDC ; 
#define  PGP_COMPR_BZIP2 131 
#define  PGP_COMPR_NONE 130 
#define  PGP_COMPR_ZIP 129 
#define  PGP_COMPR_ZLIB 128 
 int PXE_PGP_CORRUPT_DATA ; 
 int pgp_decompress_filter (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int process_data_packets (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pullf_free (int /*<<< orphan*/ *) ; 
 int pullf_read (int /*<<< orphan*/ *,int,int**) ; 
 int /*<<< orphan*/  px_debug (char*) ; 

__attribute__((used)) static int
parse_compressed_data(PGP_Context *ctx, MBuf *dst, PullFilter *pkt)
{
	int			res;
	uint8		type;
	PullFilter *pf_decompr;
	uint8	   *discard_buf;

	GETBYTE(pkt, type);

	ctx->compress_algo = type;
	switch (type)
	{
		case PGP_COMPR_NONE:
			res = process_data_packets(ctx, dst, pkt, NO_COMPR, NO_MDC);
			break;

		case PGP_COMPR_ZIP:
		case PGP_COMPR_ZLIB:
			res = pgp_decompress_filter(&pf_decompr, ctx, pkt);
			if (res >= 0)
			{
				res = process_data_packets(ctx, dst, pf_decompr,
										   NO_COMPR, NO_MDC);
				pullf_free(pf_decompr);
			}
			break;

		case PGP_COMPR_BZIP2:
			px_debug("parse_compressed_data: bzip2 unsupported");
			/* report error in pgp_decrypt() */
			ctx->unsupported_compr = 1;

			/*
			 * Discard the compressed data, allowing it to first affect any
			 * MDC digest computation.
			 */
			while (1)
			{
				res = pullf_read(pkt, 32 * 1024, &discard_buf);
				if (res <= 0)
					break;
			}

			break;

		default:
			px_debug("parse_compressed_data: unknown compr type");
			res = PXE_PGP_CORRUPT_DATA;
	}

	return res;
}