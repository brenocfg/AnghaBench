#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sess_key_len; int /*<<< orphan*/  sess_key; int /*<<< orphan*/  cipher_algo; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_Context ;
typedef  TYPE_1__ PGP_CFB ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_COMPR ; 
 int /*<<< orphan*/  NO_MDC ; 
 int pgp_cfb_create (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgp_cfb_free (TYPE_1__*) ; 
 int /*<<< orphan*/  pgp_decrypt_filter ; 
 int /*<<< orphan*/  prefix_filter ; 
 int process_data_packets (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pullf_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_symenc_data(PGP_Context *ctx, PullFilter *pkt, MBuf *dst)
{
	int			res;
	PGP_CFB    *cfb = NULL;
	PullFilter *pf_decrypt = NULL;
	PullFilter *pf_prefix = NULL;

	res = pgp_cfb_create(&cfb, ctx->cipher_algo,
						 ctx->sess_key, ctx->sess_key_len, 1, NULL);
	if (res < 0)
		goto out;

	res = pullf_create(&pf_decrypt, &pgp_decrypt_filter, cfb, pkt);
	if (res < 0)
		goto out;

	res = pullf_create(&pf_prefix, &prefix_filter, ctx, pf_decrypt);
	if (res < 0)
		goto out;

	res = process_data_packets(ctx, dst, pf_prefix, ALLOW_COMPR, NO_MDC);

out:
	if (pf_prefix)
		pullf_free(pf_prefix);
	if (pf_decrypt)
		pullf_free(pf_decrypt);
	if (cfb)
		pgp_cfb_free(cfb);

	return res;
}