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
struct TYPE_8__ {TYPE_1__* n; } ;
struct TYPE_9__ {TYPE_2__ rsa; } ;
struct TYPE_10__ {TYPE_3__ pub; } ;
struct TYPE_7__ {scalar_t__ bytes; } ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  TYPE_4__ PGP_PubKey ;
typedef  int /*<<< orphan*/  PGP_MPI ;
typedef  int /*<<< orphan*/  PGP_Context ;

/* Variables and functions */
 int create_secmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  pgp_mpi_free (int /*<<< orphan*/ *) ; 
 int pgp_mpi_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pgp_rsa_encrypt (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
encrypt_and_write_rsa(PGP_Context *ctx, PGP_PubKey *pk, PushFilter *pkt)
{
	int			res;
	PGP_MPI    *m = NULL,
			   *c = NULL;

	/* create padded msg */
	res = create_secmsg(ctx, &m, pk->pub.rsa.n->bytes - 1);
	if (res < 0)
		goto err;

	/* encrypt it */
	res = pgp_rsa_encrypt(pk, m, &c);
	if (res < 0)
		goto err;

	/* write out */
	res = pgp_mpi_write(pkt, c);

err:
	pgp_mpi_free(m);
	pgp_mpi_free(c);
	return res;
}