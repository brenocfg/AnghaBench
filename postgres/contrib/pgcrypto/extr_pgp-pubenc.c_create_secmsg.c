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
typedef  unsigned int uint8 ;
struct TYPE_3__ {int sess_key_len; unsigned int cipher_algo; scalar_t__* sess_key; } ;
typedef  int /*<<< orphan*/  PGP_MPI ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,scalar_t__*,int) ; 
 int pad_eme_pkcs1_v15 (unsigned int*,int,int,unsigned int**) ; 
 int pgp_mpi_create (unsigned int*,int,int /*<<< orphan*/ **) ; 
 unsigned int* px_alloc (int) ; 
 int /*<<< orphan*/  px_free (unsigned int*) ; 
 int /*<<< orphan*/  px_memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
create_secmsg(PGP_Context *ctx, PGP_MPI **msg_p, int full_bytes)
{
	uint8	   *secmsg;
	int			res,
				i;
	unsigned	cksum = 0;
	int			klen = ctx->sess_key_len;
	uint8	   *padded = NULL;
	PGP_MPI    *m = NULL;

	/* calc checksum */
	for (i = 0; i < klen; i++)
		cksum += ctx->sess_key[i];

	/*
	 * create "secret message"
	 */
	secmsg = px_alloc(klen + 3);
	secmsg[0] = ctx->cipher_algo;
	memcpy(secmsg + 1, ctx->sess_key, klen);
	secmsg[klen + 1] = (cksum >> 8) & 0xFF;
	secmsg[klen + 2] = cksum & 0xFF;

	/*
	 * now create a large integer of it
	 */
	res = pad_eme_pkcs1_v15(secmsg, klen + 3, full_bytes, &padded);
	if (res >= 0)
	{
		/* first byte will be 0x02 */
		int			full_bits = full_bytes * 8 - 6;

		res = pgp_mpi_create(padded, full_bits, &m);
	}

	if (padded)
	{
		px_memset(padded, 0, full_bytes);
		px_free(padded);
	}
	px_memset(secmsg, 0, klen + 3);
	px_free(secmsg);

	if (res >= 0)
		*msg_p = m;

	return res;
}