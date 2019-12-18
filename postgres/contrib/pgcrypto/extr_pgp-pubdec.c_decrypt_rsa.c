#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ algo; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_1__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;

/* Variables and functions */
 scalar_t__ PGP_PUB_RSA_ENCRYPT ; 
 scalar_t__ PGP_PUB_RSA_ENCRYPT_SIGN ; 
 int PXE_PGP_WRONG_KEY ; 
 int /*<<< orphan*/  pgp_mpi_free (int /*<<< orphan*/ *) ; 
 int pgp_mpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int pgp_rsa_decrypt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
decrypt_rsa(PGP_PubKey *pk, PullFilter *pkt, PGP_MPI **m_p)
{
	int			res;
	PGP_MPI    *c;

	if (pk->algo != PGP_PUB_RSA_ENCRYPT
		&& pk->algo != PGP_PUB_RSA_ENCRYPT_SIGN)
		return PXE_PGP_WRONG_KEY;

	/* read rsa encrypted data */
	res = pgp_mpi_read(pkt, &c);
	if (res < 0)
		return res;

	/* decrypt */
	res = pgp_rsa_decrypt(pk, c, m_p);

	pgp_mpi_free(c);
	return res;
}