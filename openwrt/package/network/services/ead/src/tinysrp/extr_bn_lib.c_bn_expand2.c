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
struct TYPE_6__ {int dmax; int top; int max; scalar_t__* d; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 scalar_t__ BN_get_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

BIGNUM *bn_expand2(BIGNUM *b, int words)
	{
	BN_ULONG *A,*a;
	const BN_ULONG *B;
	int i;

	bn_check_top(b);

	if (words > b->dmax)
		{
		bn_check_top(b);
		if (BN_get_flags(b,BN_FLG_STATIC_DATA))
			{
			return(NULL);
			}
		a=A=(BN_ULONG *)malloc(sizeof(BN_ULONG)*(words+1));
		if (A == NULL)
			{
			return(NULL);
			}
#if 1
		B=b->d;
		/* Check if the previous number needs to be copied */
		if (B != NULL)
			{
#if 0
			/* This lot is an unrolled loop to copy b->top
			 * BN_ULONGs from B to A
			 */
/*
 * I have nothing against unrolling but it's usually done for
 * several reasons, namely:
 * - minimize percentage of decision making code, i.e. branches;
 * - avoid cache trashing;
 * - make it possible to schedule loads earlier;
 * Now let's examine the code below. The cornerstone of C is
 * "programmer is always right" and that's what we love it for:-)
 * For this very reason C compilers have to be paranoid when it
 * comes to data aliasing and assume the worst. Yeah, but what
 * does it mean in real life? This means that loop body below will
 * be compiled to sequence of loads immediately followed by stores
 * as compiler assumes the worst, something in A==B+1 style. As a
 * result CPU pipeline is going to starve for incoming data. Secondly
 * if A and B happen to share same cache line such code is going to
 * cause severe cache trashing. Both factors have severe impact on
 * performance of modern CPUs and this is the reason why this
 * particular piece of code is #ifdefed away and replaced by more
 * "friendly" version found in #else section below. This comment
 * also applies to BN_copy function.
 *
 *                                      <appro@fy.chalmers.se>
 */
			for (i=b->top&(~7); i>0; i-=8)
				{
				A[0]=B[0]; A[1]=B[1]; A[2]=B[2]; A[3]=B[3];
				A[4]=B[4]; A[5]=B[5]; A[6]=B[6]; A[7]=B[7];
				A+=8;
				B+=8;
				}
			switch (b->top&7)
				{
			case 7:
				A[6]=B[6];
			case 6:
				A[5]=B[5];
			case 5:
				A[4]=B[4];
			case 4:
				A[3]=B[3];
			case 3:
				A[2]=B[2];
			case 2:
				A[1]=B[1];
			case 1:
				A[0]=B[0];
			case 0:
				/* I need the 'case 0' entry for utrix cc.
				 * If the optimizer is turned on, it does the
				 * switch table by doing
				 * a=top&7
				 * a--;
				 * goto jump_table[a];
				 * If top is 0, this makes us jump to 0xffffffc
				 * which is rather bad :-(.
				 * eric 23-Apr-1998
				 */
				;
				}
#else
			for (i=b->top>>2; i>0; i--,A+=4,B+=4)
				{
				/*
				 * The fact that the loop is unrolled
				 * 4-wise is a tribute to Intel. It's
				 * the one that doesn't have enough
				 * registers to accomodate more data.
				 * I'd unroll it 8-wise otherwise:-)
				 *
				 *              <appro@fy.chalmers.se>
				 */
				BN_ULONG a0,a1,a2,a3;
				a0=B[0]; a1=B[1]; a2=B[2]; a3=B[3];
				A[0]=a0; A[1]=a1; A[2]=a2; A[3]=a3;
				}
			switch (b->top&3)
				{
				case 3: A[2]=B[2];
				case 2: A[1]=B[1];
				case 1: A[0]=B[0];
				case 0: ; /* ultrix cc workaround, see above */
				}
#endif
			free(b->d);
			}

		b->d=a;
		b->dmax=words;

		/* Now need to zero any data between b->top and b->max */

		A= &(b->d[b->top]);
		for (i=(b->dmax - b->top)>>3; i>0; i--,A+=8)
			{
			A[0]=0; A[1]=0; A[2]=0; A[3]=0;
			A[4]=0; A[5]=0; A[6]=0; A[7]=0;
			}
		for (i=(b->dmax - b->top)&7; i>0; i--,A++)
			A[0]=0;
#else
			memset(A,0,sizeof(BN_ULONG)*(words+1));
			memcpy(A,b->d,sizeof(b->d[0])*b->top);
			b->d=a;
			b->max=words;
#endif

/*              memset(&(p[b->max]),0,((words+1)-b->max)*sizeof(BN_ULONG)); */
/*      { int i; for (i=b->max; i<words+1; i++) p[i]=i;} */

		}
	return(b);
	}