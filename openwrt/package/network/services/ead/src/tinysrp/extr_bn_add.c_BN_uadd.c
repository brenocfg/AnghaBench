#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int top; int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_MASK2 ; 
 int bn_add_words (int*,int*,int*,int) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 

int BN_uadd(BIGNUM *r, const BIGNUM *a, const BIGNUM *b)
	{
	register int i;
	int max,min;
	BN_ULONG *ap,*bp,*rp,carry,t1;
	const BIGNUM *tmp;

	bn_check_top(a);
	bn_check_top(b);

	if (a->top < b->top)
		{ tmp=a; a=b; b=tmp; }
	max=a->top;
	min=b->top;

	if (bn_wexpand(r,max+1) == NULL)
		return(0);

	r->top=max;


	ap=a->d;
	bp=b->d;
	rp=r->d;
	carry=0;

	carry=bn_add_words(rp,ap,bp,min);
	rp+=min;
	ap+=min;
	bp+=min;
	i=min;

	if (carry)
		{
		while (i < max)
			{
			i++;
			t1= *(ap++);
			if ((*(rp++)=(t1+1)&BN_MASK2) >= t1)
				{
				carry=0;
				break;
				}
			}
		if ((i >= max) && carry)
			{
			*(rp++)=1;
			r->top++;
			}
		}
	if (rp != ap)
		{
		for (; i<max; i++)
			*(rp++)= *(ap++);
		}
	/* memcpy(rp,ap,sizeof(*ap)*(max-i));*/
	return(1);
	}