#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  x; } ;
struct TYPE_16__ {int /*<<< orphan*/  u; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; } ;
struct TYPE_14__ {int /*<<< orphan*/  x; } ;
struct TYPE_20__ {TYPE_7__ dsa; TYPE_4__ rsa; TYPE_2__ elg; } ;
struct TYPE_17__ {int /*<<< orphan*/  y; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_15__ {int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  g; int /*<<< orphan*/  p; } ;
struct TYPE_18__ {TYPE_5__ dsa; TYPE_3__ rsa; TYPE_1__ elg; } ;
struct TYPE_21__ {int algo; TYPE_8__ sec; TYPE_6__ pub; } ;
typedef  TYPE_9__ PGP_PubKey ;

/* Variables and functions */
#define  PGP_PUB_DSA_SIGN 132 
#define  PGP_PUB_ELG_ENCRYPT 131 
#define  PGP_PUB_RSA_ENCRYPT 130 
#define  PGP_PUB_RSA_ENCRYPT_SIGN 129 
#define  PGP_PUB_RSA_SIGN 128 
 int /*<<< orphan*/  pgp_mpi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_free (TYPE_9__*) ; 
 int /*<<< orphan*/  px_memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

void
pgp_key_free(PGP_PubKey *pk)
{
	if (pk == NULL)
		return;

	switch (pk->algo)
	{
		case PGP_PUB_ELG_ENCRYPT:
			pgp_mpi_free(pk->pub.elg.p);
			pgp_mpi_free(pk->pub.elg.g);
			pgp_mpi_free(pk->pub.elg.y);
			pgp_mpi_free(pk->sec.elg.x);
			break;
		case PGP_PUB_RSA_SIGN:
		case PGP_PUB_RSA_ENCRYPT:
		case PGP_PUB_RSA_ENCRYPT_SIGN:
			pgp_mpi_free(pk->pub.rsa.n);
			pgp_mpi_free(pk->pub.rsa.e);
			pgp_mpi_free(pk->sec.rsa.d);
			pgp_mpi_free(pk->sec.rsa.p);
			pgp_mpi_free(pk->sec.rsa.q);
			pgp_mpi_free(pk->sec.rsa.u);
			break;
		case PGP_PUB_DSA_SIGN:
			pgp_mpi_free(pk->pub.dsa.p);
			pgp_mpi_free(pk->pub.dsa.q);
			pgp_mpi_free(pk->pub.dsa.g);
			pgp_mpi_free(pk->pub.dsa.y);
			pgp_mpi_free(pk->sec.dsa.x);
			break;
	}
	px_memset(pk, 0, sizeof(*pk));
	px_free(pk);
}