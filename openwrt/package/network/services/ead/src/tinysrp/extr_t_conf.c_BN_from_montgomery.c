#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int* d; int top; int neg; } ;
struct TYPE_25__ {int ri; int n0; TYPE_2__ N; TYPE_2__ Ni; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_2__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 TYPE_2__* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 long long BN_MASK2 ; 
 int /*<<< orphan*/  BN_add (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BN_copy (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BN_mask_bits (TYPE_2__*,int) ; 
 int /*<<< orphan*/  BN_mul (TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ BN_ucmp (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BN_usub (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bn_fix_top (TYPE_2__*) ; 
 int bn_mul_add_words (int*,int*,int,int) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

int BN_from_montgomery(BIGNUM *ret, BIGNUM *a, BN_MONT_CTX *mont,
	     BN_CTX *ctx)
	{
	int retn=0;

#ifdef MONT_WORD
	BIGNUM *n,*r;
	BN_ULONG *ap,*np,*rp,n0,v,*nrp;
	int al,nl,max,i,x,ri;

	BN_CTX_start(ctx);
	if ((r = BN_CTX_get(ctx)) == NULL) goto err;

	if (!BN_copy(r,a)) goto err;
	n= &(mont->N);

	ap=a->d;
	/* mont->ri is the size of mont->N in bits (rounded up
	   to the word size) */
	al=ri=mont->ri/BN_BITS2;

	nl=n->top;
	if ((al == 0) || (nl == 0)) { r->top=0; return(1); }

	max=(nl+al+1); /* allow for overflow (no?) XXX */
	if (bn_wexpand(r,max) == NULL) goto err;
	if (bn_wexpand(ret,max) == NULL) goto err;

	r->neg=a->neg^n->neg;
	np=n->d;
	rp=r->d;
	nrp= &(r->d[nl]);

	/* clear the top words of T */
#if 1
	for (i=r->top; i<max; i++) /* memset? XXX */
		r->d[i]=0;
#else
	memset(&(r->d[r->top]),0,(max-r->top)*sizeof(BN_ULONG));
#endif

	r->top=max;
	n0=mont->n0;

#ifdef BN_COUNT
	printf("word BN_from_montgomery %d * %d\n",nl,nl);
#endif
	for (i=0; i<nl; i++)
		{
#ifdef __TANDEM
		{
		   long long t1;
		   long long t2;
		   long long t3;
		   t1 = rp[0] * (n0 & 0177777);
		   t2 = 037777600000l;
		   t2 = n0 & t2;
		   t3 = rp[0] & 0177777;
		   t2 = (t3 * t2) & BN_MASK2;
		   t1 = t1 + t2;
		   v=bn_mul_add_words(rp,np,nl,(BN_ULONG) t1);
		}
#else
		v=bn_mul_add_words(rp,np,nl,(rp[0]*n0)&BN_MASK2);
#endif
		nrp++;
		rp++;
		if (((nrp[-1]+=v)&BN_MASK2) >= v)
			continue;
		else
			{
			if (((++nrp[0])&BN_MASK2) != 0) continue;
			if (((++nrp[1])&BN_MASK2) != 0) continue;
			for (x=2; (((++nrp[x])&BN_MASK2) == 0); x++) ;
			}
		}
	bn_fix_top(r);

	/* mont->ri will be a multiple of the word size */
#if 0
	BN_rshift(ret,r,mont->ri);
#else
	ret->neg = r->neg;
	x=ri;
	rp=ret->d;
	ap= &(r->d[x]);
	if (r->top < x)
		al=0;
	else
		al=r->top-x;
	ret->top=al;
	al-=4;
	for (i=0; i<al; i+=4)
		{
		BN_ULONG t1,t2,t3,t4;

		t1=ap[i+0];
		t2=ap[i+1];
		t3=ap[i+2];
		t4=ap[i+3];
		rp[i+0]=t1;
		rp[i+1]=t2;
		rp[i+2]=t3;
		rp[i+3]=t4;
		}
	al+=4;
	for (; i<al; i++)
		rp[i]=ap[i];
#endif
#else /* !MONT_WORD */
	BIGNUM *t1,*t2;

	BN_CTX_start(ctx);
	t1 = BN_CTX_get(ctx);
	t2 = BN_CTX_get(ctx);
	if (t1 == NULL || t2 == NULL) goto err;

	if (!BN_copy(t1,a)) goto err;
	BN_mask_bits(t1,mont->ri);

	if (!BN_mul(t2,t1,&mont->Ni,ctx)) goto err;
	BN_mask_bits(t2,mont->ri);

	if (!BN_mul(t1,t2,&mont->N,ctx)) goto err;
	if (!BN_add(t2,a,t1)) goto err;
	BN_rshift(ret,t2,mont->ri);
#endif /* MONT_WORD */

	if (BN_ucmp(ret, &(mont->N)) >= 0)
		{
		BN_usub(ret,ret,&(mont->N));
		}
	retn=1;
 err:
	BN_CTX_end(ctx);
	return(retn);
	}