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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_9__ {int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  u; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; } ;
struct TYPE_7__ {int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_3__ dsa; TYPE_2__ rsa; TYPE_1__ elg; } ;
struct TYPE_11__ {int algo; TYPE_4__ sec; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  int /*<<< orphan*/  PX_MD ;
typedef  TYPE_5__ PGP_PubKey ;

/* Variables and functions */
 int /*<<< orphan*/  PGP_DIGEST_SHA1 ; 
#define  PGP_PUB_DSA_SIGN 132 
#define  PGP_PUB_ELG_ENCRYPT 131 
#define  PGP_PUB_RSA_ENCRYPT 130 
#define  PGP_PUB_RSA_ENCRYPT_SIGN 129 
#define  PGP_PUB_RSA_SIGN 128 
 int PXE_PGP_KEYPKT_CORRUPT ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pgp_load_digest (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pgp_mpi_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pullf_read_fixed (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_debug (char*) ; 
 int /*<<< orphan*/  px_md_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
check_key_sha1(PullFilter *src, PGP_PubKey *pk)
{
	int			res;
	uint8		got_sha1[20];
	uint8		my_sha1[20];
	PX_MD	   *md;

	res = pullf_read_fixed(src, 20, got_sha1);
	if (res < 0)
		return res;

	res = pgp_load_digest(PGP_DIGEST_SHA1, &md);
	if (res < 0)
		goto err;
	switch (pk->algo)
	{
		case PGP_PUB_ELG_ENCRYPT:
			pgp_mpi_hash(md, pk->sec.elg.x);
			break;
		case PGP_PUB_RSA_SIGN:
		case PGP_PUB_RSA_ENCRYPT:
		case PGP_PUB_RSA_ENCRYPT_SIGN:
			pgp_mpi_hash(md, pk->sec.rsa.d);
			pgp_mpi_hash(md, pk->sec.rsa.p);
			pgp_mpi_hash(md, pk->sec.rsa.q);
			pgp_mpi_hash(md, pk->sec.rsa.u);
			break;
		case PGP_PUB_DSA_SIGN:
			pgp_mpi_hash(md, pk->sec.dsa.x);
			break;
	}
	px_md_finish(md, my_sha1);
	px_md_free(md);

	if (memcmp(my_sha1, got_sha1, 20) != 0)
	{
		px_debug("key sha1 check failed");
		res = PXE_PGP_KEYPKT_CORRUPT;
	}
err:
	px_memset(got_sha1, 0, 20);
	px_memset(my_sha1, 0, 20);
	return res;
}