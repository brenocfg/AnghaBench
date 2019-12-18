#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  sgemv_ (char*,int const*,int const*,float const*,float const*,int const*,float const*,int const*,float const*,float*,int const*) ; 

void sgemv (char *trans,
            const int *m, const int *n,
            const float *alpha,
            const float *A, const int *lda,
            const float *B, const int *incB,
            const float *beta,
            float *C, const int *incC)
{
    sgemv_(trans,m,n,alpha,A,lda,B,incB,beta,C,incC);
}