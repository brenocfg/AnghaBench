#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int* d; } ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 TYPE_1__ const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_from_montgomery (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_init (TYPE_1__ const*) ; 
 scalar_t__ BN_is_bit_set (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  BN_mod (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul_montgomery (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_num_bits (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_one (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_to_montgomery (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_ucmp (TYPE_1__ const*,TYPE_1__ const*) ; 
 TYPE_1__ const* BN_value_one () ; 
 int BN_window_bits_for_exponent_size (int) ; 
 int TABLE_SIZE ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 

int BN_mod_exp_mont(BIGNUM *rr, BIGNUM *a, const BIGNUM *p,
		    const BIGNUM *m, BN_CTX *ctx, BN_MONT_CTX *in_mont)
	{
	int i,j,bits,ret=0,wstart,wend,window,wvalue;
	int start=1,ts=0;
	BIGNUM *d,*r;
	BIGNUM *aa;
	BIGNUM val[TABLE_SIZE];
	BN_MONT_CTX *mont=NULL;

	bn_check_top(a);
	bn_check_top(p);
	bn_check_top(m);

	if (!(m->d[0] & 1))
		{
		return(0);
		}
	bits=BN_num_bits(p);
	if (bits == 0)
		{
		BN_one(rr);
		return(1);
		}
	BN_CTX_start(ctx);
	d = BN_CTX_get(ctx);
	r = BN_CTX_get(ctx);
	if (d == NULL || r == NULL) goto err;

	/* If this is not done, things will break in the montgomery
	 * part */

	if (in_mont != NULL)
		mont=in_mont;
	else
		{
		if ((mont=BN_MONT_CTX_new()) == NULL) goto err;
		if (!BN_MONT_CTX_set(mont,m,ctx)) goto err;
		}

	BN_init(&val[0]);
	ts=1;
	if (BN_ucmp(a,m) >= 0)
		{
		if (!BN_mod(&(val[0]),a,m,ctx))
			goto err;
		aa= &(val[0]);
		}
	else
		aa=a;
	if (!BN_to_montgomery(&(val[0]),aa,mont,ctx)) goto err; /* 1 */

	window = BN_window_bits_for_exponent_size(bits);
	if (window > 1)
		{
		if (!BN_mod_mul_montgomery(d,&(val[0]),&(val[0]),mont,ctx)) goto err; /* 2 */
		j=1<<(window-1);
		for (i=1; i<j; i++)
			{
			BN_init(&(val[i]));
			if (!BN_mod_mul_montgomery(&(val[i]),&(val[i-1]),d,mont,ctx))
				goto err;
			}
		ts=i;
		}

	start=1;        /* This is used to avoid multiplication etc
			 * when there is only the value '1' in the
			 * buffer. */
	wvalue=0;       /* The 'value' of the window */
	wstart=bits-1;  /* The top bit of the window */
	wend=0;         /* The bottom bit of the window */

	if (!BN_to_montgomery(r,BN_value_one(),mont,ctx)) goto err;
	for (;;)
		{
		if (BN_is_bit_set(p,wstart) == 0)
			{
			if (!start)
				{
				if (!BN_mod_mul_montgomery(r,r,r,mont,ctx))
				goto err;
				}
			if (wstart == 0) break;
			wstart--;
			continue;
			}
		/* We now have wstart on a 'set' bit, we now need to work out
		 * how bit a window to do.  To do this we need to scan
		 * forward until the last set bit before the end of the
		 * window */
		j=wstart;
		wvalue=1;
		wend=0;
		for (i=1; i<window; i++)
			{
			if (wstart-i < 0) break;
			if (BN_is_bit_set(p,wstart-i))
				{
				wvalue<<=(i-wend);
				wvalue|=1;
				wend=i;
				}
			}

		/* wend is the size of the current window */
		j=wend+1;
		/* add the 'bytes above' */
		if (!start)
			for (i=0; i<j; i++)
				{
				if (!BN_mod_mul_montgomery(r,r,r,mont,ctx))
					goto err;
				}

		/* wvalue will be an odd number < 2^window */
		if (!BN_mod_mul_montgomery(r,r,&(val[wvalue>>1]),mont,ctx))
			goto err;

		/* move the 'window' down further */
		wstart-=wend+1;
		wvalue=0;
		start=0;
		if (wstart < 0) break;
		}
	if (!BN_from_montgomery(rr,r,mont,ctx)) goto err;
	ret=1;
err:
	if ((in_mont == NULL) && (mont != NULL)) BN_MONT_CTX_free(mont);
	BN_CTX_end(ctx);
	for (i=0; i<ts; i++)
		BN_clear_free(&(val[i]));
	return(ret);
	}