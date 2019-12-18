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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/ * pub_key; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  int /*<<< orphan*/  PGP_PubKey ;
typedef  TYPE_1__ PGP_Context ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int internal_read_key (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int,int) ; 
 int pullf_create_mbuf_reader (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pullf_free (int /*<<< orphan*/ *) ; 

int
pgp_set_pubkey(PGP_Context *ctx, MBuf *keypkt,
			   const uint8 *key, int key_len, int pubtype)
{
	int			res;
	PullFilter *src;
	PGP_PubKey *pk = NULL;

	res = pullf_create_mbuf_reader(&src, keypkt);
	if (res < 0)
		return res;

	res = internal_read_key(src, &pk, key, key_len, pubtype);
	pullf_free(src);

	if (res >= 0)
		ctx->pub_key = pk;

	return res < 0 ? res : 0;
}