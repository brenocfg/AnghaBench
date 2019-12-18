#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_6__ {int top; int* d; int /*<<< orphan*/  neg; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int BN_MASK2 ; 
 int /*<<< orphan*/  bn_fix_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int BN_lshift(BIGNUM *r, const BIGNUM *a, int n)
	{
	int i,nw,lb,rb;
	BN_ULONG *t,*f;
	BN_ULONG l;

	r->neg=a->neg;
	if (bn_wexpand(r,a->top+(n/BN_BITS2)+1) == NULL) return(0);
	nw=n/BN_BITS2;
	lb=n%BN_BITS2;
	rb=BN_BITS2-lb;
	f=a->d;
	t=r->d;
	t[a->top+nw]=0;
	if (lb == 0)
		for (i=a->top-1; i>=0; i--)
			t[nw+i]=f[i];
	else
		for (i=a->top-1; i>=0; i--)
			{
			l=f[i];
			t[nw+i+1]|=(l>>rb)&BN_MASK2;
			t[nw+i]=(l<<lb)&BN_MASK2;
			}
	memset(t,0,nw*sizeof(t[0]));
/*      for (i=0; i<nw; i++)
		t[i]=0;*/
	r->top=a->top+nw+1;
	bn_fix_top(r);
	return(1);
	}