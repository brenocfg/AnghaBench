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
struct TYPE_3__ {int mode; int digest_algo; int /*<<< orphan*/  iter; int /*<<< orphan*/ * salt; } ;
typedef  TYPE_1__ PGP_S2K ;

/* Variables and functions */
#define  PGP_S2K_ISALTED 130 
 int PGP_S2K_SALT ; 
#define  PGP_S2K_SALTED 129 
#define  PGP_S2K_SIMPLE 128 
 int PXE_NO_RANDOM ; 
 int PXE_PGP_BAD_S2K_MODE ; 
 int /*<<< orphan*/  decide_s2k_iter (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_strong_random (int /*<<< orphan*/ *,int) ; 

int
pgp_s2k_fill(PGP_S2K *s2k, int mode, int digest_algo, int count)
{
	int			res = 0;
	uint8		tmp;

	s2k->mode = mode;
	s2k->digest_algo = digest_algo;

	switch (s2k->mode)
	{
		case PGP_S2K_SIMPLE:
			break;
		case PGP_S2K_SALTED:
			if (!pg_strong_random(s2k->salt, PGP_S2K_SALT))
				return PXE_NO_RANDOM;
			break;
		case PGP_S2K_ISALTED:
			if (!pg_strong_random(s2k->salt, PGP_S2K_SALT))
				return PXE_NO_RANDOM;
			if (!pg_strong_random(&tmp, 1))
				return PXE_NO_RANDOM;
			s2k->iter = decide_s2k_iter(tmp, count);
			break;
		default:
			res = PXE_PGP_BAD_S2K_MODE;
	}
	return res;
}