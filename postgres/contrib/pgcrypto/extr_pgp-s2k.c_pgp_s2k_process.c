#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_6__ {scalar_t__ key_len; int mode; int /*<<< orphan*/  digest_algo; } ;
typedef  int /*<<< orphan*/  PX_MD ;
typedef  TYPE_1__ PGP_S2K ;

/* Variables and functions */
 int PXE_PGP_BAD_S2K_MODE ; 
 int PXE_PGP_UNSUPPORTED_CIPHER ; 
 int calc_s2k_iter_salted (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int calc_s2k_salted (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int calc_s2k_simple (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ pgp_get_cipher_key_size (int) ; 
 int pgp_load_digest (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  px_md_free (int /*<<< orphan*/ *) ; 

int
pgp_s2k_process(PGP_S2K *s2k, int cipher, const uint8 *key, int key_len)
{
	int			res;
	PX_MD	   *md;

	s2k->key_len = pgp_get_cipher_key_size(cipher);
	if (s2k->key_len <= 0)
		return PXE_PGP_UNSUPPORTED_CIPHER;

	res = pgp_load_digest(s2k->digest_algo, &md);
	if (res < 0)
		return res;

	switch (s2k->mode)
	{
		case 0:
			res = calc_s2k_simple(s2k, md, key, key_len);
			break;
		case 1:
			res = calc_s2k_salted(s2k, md, key, key_len);
			break;
		case 3:
			res = calc_s2k_iter_salted(s2k, md, key, key_len);
			break;
		default:
			res = PXE_PGP_BAD_S2K_MODE;
	}
	px_md_free(md);
	return res;
}