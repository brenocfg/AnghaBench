#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int top; scalar_t__* d; scalar_t__ neg; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_sqr_comba4 (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bn_sqr_comba8 (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bn_sqr_normal (scalar_t__*,scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int BN_sqr(BIGNUM *r, BIGNUM *a, BN_CTX *ctx)
	{
	int max,al;
	int ret = 0;
	BIGNUM *tmp,*rr;

#ifdef BN_COUNT
printf("BN_sqr %d * %d\n",a->top,a->top);
#endif
	bn_check_top(a);

	al=a->top;
	if (al <= 0)
		{
		r->top=0;
		return(1);
		}

	BN_CTX_start(ctx);
	rr=(a != r) ? r : BN_CTX_get(ctx);
	tmp=BN_CTX_get(ctx);
	if (tmp == NULL) goto err;

	max=(al+al);
	if (bn_wexpand(rr,max+1) == NULL) goto err;

	r->neg=0;
	if (al == 4)
		{
#ifndef BN_SQR_COMBA
		BN_ULONG t[8];
		bn_sqr_normal(rr->d,a->d,4,t);
#else
		bn_sqr_comba4(rr->d,a->d);
#endif
		}
	else if (al == 8)
		{
#ifndef BN_SQR_COMBA
		BN_ULONG t[16];
		bn_sqr_normal(rr->d,a->d,8,t);
#else
		bn_sqr_comba8(rr->d,a->d);
#endif
		}
	else
		{
		if (bn_wexpand(tmp,max) == NULL) goto err;
		bn_sqr_normal(rr->d,a->d,al,tmp->d);
		}

	rr->top=max;
	if ((max > 0) && (rr->d[max-1] == 0)) rr->top--;
	if (rr != r) BN_copy(r,rr);
	ret = 1;
 err:
	BN_CTX_end(ctx);
	return(ret);
	}