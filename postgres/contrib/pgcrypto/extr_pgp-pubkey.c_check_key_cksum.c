#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8 ;
struct TYPE_9__ {int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  u; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; } ;
struct TYPE_7__ {int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_3__ dsa; TYPE_2__ rsa; TYPE_1__ elg; } ;
struct TYPE_11__ {int algo; TYPE_4__ sec; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_5__ PGP_PubKey ;

/* Variables and functions */
#define  PGP_PUB_DSA_SIGN 132 
#define  PGP_PUB_ELG_ENCRYPT 131 
#define  PGP_PUB_RSA_ENCRYPT 130 
#define  PGP_PUB_RSA_ENCRYPT_SIGN 129 
#define  PGP_PUB_RSA_SIGN 128 
 int PXE_PGP_KEYPKT_CORRUPT ; 
 unsigned int pgp_mpi_cksum (unsigned int,int /*<<< orphan*/ ) ; 
 int pullf_read_fixed (int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  px_debug (char*) ; 

__attribute__((used)) static int
check_key_cksum(PullFilter *src, PGP_PubKey *pk)
{
	int			res;
	unsigned	got_cksum,
				my_cksum = 0;
	uint8		buf[2];

	res = pullf_read_fixed(src, 2, buf);
	if (res < 0)
		return res;

	got_cksum = ((unsigned) buf[0] << 8) + buf[1];
	switch (pk->algo)
	{
		case PGP_PUB_ELG_ENCRYPT:
			my_cksum = pgp_mpi_cksum(0, pk->sec.elg.x);
			break;
		case PGP_PUB_RSA_SIGN:
		case PGP_PUB_RSA_ENCRYPT:
		case PGP_PUB_RSA_ENCRYPT_SIGN:
			my_cksum = pgp_mpi_cksum(0, pk->sec.rsa.d);
			my_cksum = pgp_mpi_cksum(my_cksum, pk->sec.rsa.p);
			my_cksum = pgp_mpi_cksum(my_cksum, pk->sec.rsa.q);
			my_cksum = pgp_mpi_cksum(my_cksum, pk->sec.rsa.u);
			break;
		case PGP_PUB_DSA_SIGN:
			my_cksum = pgp_mpi_cksum(0, pk->sec.dsa.x);
			break;
	}
	if (my_cksum != got_cksum)
	{
		px_debug("key cksum check failed");
		return PXE_PGP_KEYPKT_CORRUPT;
	}
	return 0;
}