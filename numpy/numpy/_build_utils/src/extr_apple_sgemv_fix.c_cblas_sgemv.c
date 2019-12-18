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
typedef  enum CBLAS_TRANSPOSE { ____Placeholder_CBLAS_TRANSPOSE } CBLAS_TRANSPOSE ;
typedef  enum CBLAS_ORDER { ____Placeholder_CBLAS_ORDER } CBLAS_ORDER ;

/* Variables and functions */
 int const CblasColMajor ; 
 int const CblasConjTrans ; 
 int const CblasNoTrans ; 
 int const CblasRowMajor ; 
 int const CblasTrans ; 
 int /*<<< orphan*/  cblas_xerbla (int,char*,char*,int const) ; 
 int /*<<< orphan*/  sgemv_ (char*,int const*,int const*,float const*,float const*,int const*,float const*,int const*,float const*,float*,int const*) ; 

void cblas_sgemv(const enum CBLAS_ORDER order,
                 const enum CBLAS_TRANSPOSE TransA, const int M, const int N,
                 const float alpha, const float  *A, const int lda,
                 const float  *X, const int incX, const float beta,
                 float  *Y, const int incY)
{
    char TA;
    if (order == CblasColMajor)
    {
        if (TransA == CblasNoTrans) TA = 'N';
        else if (TransA == CblasTrans) TA = 'T';
        else if (TransA == CblasConjTrans) TA = 'C';
        else
        {
            cblas_xerbla(2, "cblas_sgemv","Illegal TransA setting, %d\n", TransA);
        }
        sgemv_(&TA, &M, &N, &alpha, A, &lda, X, &incX, &beta, Y, &incY);
    }
    else if (order == CblasRowMajor)
    {
        if (TransA == CblasNoTrans) TA = 'T';
        else if (TransA == CblasTrans) TA = 'N';
        else if (TransA == CblasConjTrans) TA = 'N';
        else
        {
            cblas_xerbla(2, "cblas_sgemv", "Illegal TransA setting, %d\n", TransA);
            return;
        }
        sgemv_(&TA, &N, &M, &alpha, A, &lda, X, &incX, &beta, Y, &incY);
    }
    else
        cblas_xerbla(1, "cblas_sgemv", "Illegal Order setting, %d\n", order);
}