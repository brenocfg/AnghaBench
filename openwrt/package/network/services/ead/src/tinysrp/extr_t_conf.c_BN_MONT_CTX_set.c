#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int top; int dmax; scalar_t__* d; int /*<<< orphan*/  neg; } ;
struct TYPE_24__ {int ri; int /*<<< orphan*/  N; TYPE_2__ const RR; TYPE_2__ const Ni; scalar_t__ n0; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  TYPE_1__ BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_2__ const BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int /*<<< orphan*/  BN_MASK2 ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_div (TYPE_2__ const*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_init (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_is_zero (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_lshift (TYPE_2__ const*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  BN_mod (TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_mod_inverse (TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_set_bit (TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  BN_set_word (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub_word (TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  BN_zero (TYPE_2__ const*) ; 

int BN_MONT_CTX_set(BN_MONT_CTX *mont, const BIGNUM *mod, BN_CTX *ctx)
	{
	BIGNUM Ri,*R;

	BN_init(&Ri);
	R= &(mont->RR);                                 /* grab RR as a temp */
	BN_copy(&(mont->N),mod);                        /* Set N */

#ifdef MONT_WORD
		{
		BIGNUM tmod;
		BN_ULONG buf[2];

		mont->ri=(BN_num_bits(mod)+(BN_BITS2-1))/BN_BITS2*BN_BITS2;
		BN_zero(R);
		BN_set_bit(R,BN_BITS2);                 /* R */

		buf[0]=mod->d[0]; /* tmod = N mod word size */
		buf[1]=0;
		tmod.d=buf;
		tmod.top=1;
		tmod.dmax=2;
		tmod.neg=mod->neg;
							/* Ri = R^-1 mod N*/
		if ((BN_mod_inverse(&Ri,R,&tmod,ctx)) == NULL)
			goto err;
		BN_lshift(&Ri,&Ri,BN_BITS2);            /* R*Ri */
		if (!BN_is_zero(&Ri))
			BN_sub_word(&Ri,1);
		else /* if N mod word size == 1 */
			BN_set_word(&Ri,BN_MASK2);  /* Ri-- (mod word size) */
		BN_div(&Ri,NULL,&Ri,&tmod,ctx); /* Ni = (R*Ri-1)/N,
						 * keep only least significant word: */
		mont->n0=Ri.d[0];
		BN_free(&Ri);
		}
#else /* !MONT_WORD */
		{ /* bignum version */
		mont->ri=BN_num_bits(mod);
		BN_zero(R);
		BN_set_bit(R,mont->ri);                 /* R = 2^ri */
							/* Ri = R^-1 mod N*/
		if ((BN_mod_inverse(&Ri,R,mod,ctx)) == NULL)
			goto err;
		BN_lshift(&Ri,&Ri,mont->ri);            /* R*Ri */
		BN_sub_word(&Ri,1);
							/* Ni = (R*Ri-1) / N */
		BN_div(&(mont->Ni),NULL,&Ri,mod,ctx);
		BN_free(&Ri);
		}
#endif

	/* setup RR for conversions */
	BN_zero(&(mont->RR));
	BN_set_bit(&(mont->RR),mont->ri*2);
	BN_mod(&(mont->RR),&(mont->RR),&(mont->N),ctx);

	return(1);
err:
	return(0);
	}