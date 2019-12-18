#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  g; int /*<<< orphan*/  p; } ;
struct TYPE_11__ {int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_13__ {TYPE_3__ elg; TYPE_2__ rsa; TYPE_1__ dsa; } ;
struct TYPE_14__ {int ver; int algo; int can_encrypt; TYPE_4__ pub; int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  TYPE_5__ PGP_PubKey ;

/* Variables and functions */
 int /*<<< orphan*/  GETBYTE (int /*<<< orphan*/ *,int) ; 
#define  PGP_PUB_DSA_SIGN 132 
#define  PGP_PUB_ELG_ENCRYPT 131 
#define  PGP_PUB_RSA_ENCRYPT 130 
#define  PGP_PUB_RSA_ENCRYPT_SIGN 129 
#define  PGP_PUB_RSA_SIGN 128 
 int PXE_PGP_NOT_V4_KEYPKT ; 
 int PXE_PGP_UNKNOWN_PUBALGO ; 
 int calc_key_id (TYPE_5__*) ; 
 int pgp_key_alloc (TYPE_5__**) ; 
 int /*<<< orphan*/  pgp_key_free (TYPE_5__*) ; 
 int pgp_mpi_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pullf_read_fixed (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_debug (char*,int const) ; 

int
_pgp_read_public_key(PullFilter *pkt, PGP_PubKey **pk_p)
{
	int			res;
	PGP_PubKey *pk;

	res = pgp_key_alloc(&pk);
	if (res < 0)
		return res;

	/* get version */
	GETBYTE(pkt, pk->ver);
	if (pk->ver != 4)
	{
		res = PXE_PGP_NOT_V4_KEYPKT;
		goto out;
	}

	/* read time */
	res = pullf_read_fixed(pkt, 4, pk->time);
	if (res < 0)
		goto out;

	/* pubkey algorithm */
	GETBYTE(pkt, pk->algo);

	switch (pk->algo)
	{
		case PGP_PUB_DSA_SIGN:
			res = pgp_mpi_read(pkt, &pk->pub.dsa.p);
			if (res < 0)
				break;
			res = pgp_mpi_read(pkt, &pk->pub.dsa.q);
			if (res < 0)
				break;
			res = pgp_mpi_read(pkt, &pk->pub.dsa.g);
			if (res < 0)
				break;
			res = pgp_mpi_read(pkt, &pk->pub.dsa.y);
			if (res < 0)
				break;

			res = calc_key_id(pk);
			break;

		case PGP_PUB_RSA_SIGN:
		case PGP_PUB_RSA_ENCRYPT:
		case PGP_PUB_RSA_ENCRYPT_SIGN:
			res = pgp_mpi_read(pkt, &pk->pub.rsa.n);
			if (res < 0)
				break;
			res = pgp_mpi_read(pkt, &pk->pub.rsa.e);
			if (res < 0)
				break;

			res = calc_key_id(pk);

			if (pk->algo != PGP_PUB_RSA_SIGN)
				pk->can_encrypt = 1;
			break;

		case PGP_PUB_ELG_ENCRYPT:
			res = pgp_mpi_read(pkt, &pk->pub.elg.p);
			if (res < 0)
				break;
			res = pgp_mpi_read(pkt, &pk->pub.elg.g);
			if (res < 0)
				break;
			res = pgp_mpi_read(pkt, &pk->pub.elg.y);
			if (res < 0)
				break;

			res = calc_key_id(pk);

			pk->can_encrypt = 1;
			break;

		default:
			px_debug("unknown public algo: %d", pk->algo);
			res = PXE_PGP_UNKNOWN_PUBALGO;
	}

out:
	if (res < 0)
		pgp_key_free(pk);
	else
		*pk_p = pk;

	return res;
}