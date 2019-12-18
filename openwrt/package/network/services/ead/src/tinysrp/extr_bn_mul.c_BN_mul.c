#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int top; int neg; int /*<<< orphan*/  d; } ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  BN_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_fix_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_mul_comba4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_mul_comba8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_mul_normal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int BN_mul(BIGNUM *r, BIGNUM *a, BIGNUM *b, BN_CTX *ctx)
	{
	int top,al,bl;
	BIGNUM *rr;
	int ret = 0;
#if defined(BN_MUL_COMBA) || defined(BN_RECURSION)
	int i;
#endif

#ifdef BN_COUNT
	printf("BN_mul %d * %d\n",a->top,b->top);
#endif

	bn_check_top(a);
	bn_check_top(b);
	bn_check_top(r);

	al=a->top;
	bl=b->top;

	if ((al == 0) || (bl == 0))
		{
		BN_zero(r);
		return(1);
		}
	top=al+bl;

	BN_CTX_start(ctx);
	if ((r == a) || (r == b))
		{
		if ((rr = BN_CTX_get(ctx)) == NULL) goto err;
		}
	else
		rr = r;
	rr->neg=a->neg^b->neg;

#if defined(BN_MUL_COMBA) || defined(BN_RECURSION)
	i = al-bl;
#endif
#ifdef BN_MUL_COMBA
	if (i == 0)
		{
# if 0
		if (al == 4)
			{
			if (bn_wexpand(rr,8) == NULL) goto err;
			rr->top=8;
			bn_mul_comba4(rr->d,a->d,b->d);
			goto end;
			}
# endif
		if (al == 8)
			{
			if (bn_wexpand(rr,16) == NULL) goto err;
			rr->top=16;
			bn_mul_comba8(rr->d,a->d,b->d);
			goto end;
			}
		}
#endif /* BN_MUL_COMBA */
	if (bn_wexpand(rr,top) == NULL) goto err;
	rr->top=top;
	bn_mul_normal(rr->d,a->d,al,b->d,bl);

#if defined(BN_MUL_COMBA) || defined(BN_RECURSION)
end:
#endif
	bn_fix_top(rr);
	if (r != rr) BN_copy(r,rr);
	ret=1;
err:
	BN_CTX_end(ctx);
	return(ret);
	}