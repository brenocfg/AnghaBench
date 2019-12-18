#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* p; } ;
struct TYPE_9__ {TYPE_2__ elg; } ;
struct TYPE_10__ {TYPE_3__ pub; } ;
struct TYPE_7__ {scalar_t__ bytes; } ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  TYPE_4__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;
typedef  int /*<<< orphan*/  PGP_Context ;

/* Variables and functions */
 int create_secmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 
 int pgp_elgamal_encrypt (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pgp_mpi_free (int /*<<< orphan*/ *) ; 
 int pgp_mpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
encrypt_and_write_elgamal(PGP_Context *ctx, PGP_PubKey *pk, PushFilter *pkt)
{
	int			res;
	PGP_MPI    *m = NULL,
			   *c1 = NULL,
			   *c2 = NULL;

	/* create padded msg */
	res = create_secmsg(ctx, &m, pk->pub.elg.p->bytes - 1);
	if (res < 0)
		goto err;

	/* encrypt it */
	res = pgp_elgamal_encrypt(pk, m, &c1, &c2);
	if (res < 0)
		goto err;

	/* write out */
	res = pgp_mpi_write(pkt, c1);
	if (res < 0)
		goto err;
	res = pgp_mpi_write(pkt, c2);

err:
	pgp_mpi_free(m);
	pgp_mpi_free(c1);
	pgp_mpi_free(c2);
	return res;
}