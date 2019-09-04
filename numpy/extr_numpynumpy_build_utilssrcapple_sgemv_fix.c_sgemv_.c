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
typedef  int npy_intp ;

/* Variables and functions */
 scalar_t__ AVX_and_10_9 ; 
 int /*<<< orphan*/  CblasColMajor ; 
 int /*<<< orphan*/  CblasNoTrans ; 
 int /*<<< orphan*/  CblasTrans ; 
 int /*<<< orphan*/  accelerate_cblas_sgemm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,int const,float const,float const*,int const,float const*,int const,float const,float*,int const) ; 
 int /*<<< orphan*/  accelerate_sgemv (char const*,int const*,int const*,float const*,float const*,int const*,float const*,int const*,float const*,float*,int const*) ; 
 int /*<<< orphan*/  cblas_xerbla (int,char*,char*,char const) ; 

void sgemv_( const char* trans, const int* m, const int* n,
             const float* alpha, const float* A, const int* ldA,
             const float* X, const int* incX,
             const float* beta, float* Y, const int* incY )
{
    /* It is safe to use the original SGEMV if we are not using AVX on Mavericks
     * or the input arrays A, X and Y are all aligned on 32 byte boundaries. */
    #define BADARRAY(x) (((npy_intp)(void*)x) % 32)
    const int use_sgemm = AVX_and_10_9 && (BADARRAY(A) || BADARRAY(X) || BADARRAY(Y));
    if (!use_sgemm) {
        accelerate_sgemv(trans,m,n,alpha,A,ldA,X,incX,beta,Y,incY);
        return;
    }

    /* Arrays are misaligned, the CPU supports AVX, and we are running
     * Mavericks.
     *
     * Emulation of SGEMV with SGEMM:
     *
     * SGEMV allows vectors to be strided. SGEMM requires all arrays to be
     * contiguous along the leading dimension. To emulate striding in SGEMV
     * with the leading dimension arguments in SGEMM we compute
     *
     *    Y = alpha * op(A) @ X + beta * Y
     *
     * as
     *
     *    Y.T = alpha * X.T @ op(A).T + beta * Y.T
     *
     * Because Fortran uses column major order and X.T and Y.T are row vectors,
     * the leading dimensions of X.T and Y.T in SGEMM become equal to the
     * strides of the column vectors X and Y in SGEMV. */

    switch (*trans) {
        case 'T':
        case 't':
        case 'C':
        case 'c':
            accelerate_cblas_sgemm( CblasColMajor, CblasNoTrans, CblasNoTrans,
                1, *n, *m, *alpha, X, *incX, A, *ldA, *beta, Y, *incY );
            break;
        case 'N':
        case 'n':
            accelerate_cblas_sgemm( CblasColMajor, CblasNoTrans, CblasTrans,
                1, *m, *n, *alpha, X, *incX, A, *ldA, *beta, Y, *incY );
            break;
        default:
            cblas_xerbla(1, "SGEMV", "Illegal transpose setting: %c\n", *trans);
    }
}