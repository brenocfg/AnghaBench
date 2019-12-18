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
typedef  int /*<<< orphan*/  npy_float ;
typedef  int /*<<< orphan*/  npy_double ;
typedef  int /*<<< orphan*/  npy_cfloat ;
typedef  int /*<<< orphan*/  npy_cdouble ;
typedef  enum CBLAS_TRANSPOSE { ____Placeholder_CBLAS_TRANSPOSE } CBLAS_TRANSPOSE ;
typedef  enum CBLAS_ORDER { ____Placeholder_CBLAS_ORDER } CBLAS_ORDER ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  CblasUpper ; 
#define  NPY_CDOUBLE 131 
#define  NPY_CFLOAT 130 
#define  NPY_DOUBLE 129 
#define  NPY_FLOAT 128 
 void* PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PyArray_GETPTR2 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cblas_csyrk (int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  cblas_dsyrk (int,int /*<<< orphan*/ ,int,int,int,int,void const*,int,int,void*,int) ; 
 int /*<<< orphan*/  cblas_ssyrk (int,int /*<<< orphan*/ ,int,int,int,float,void const*,int,float,void*,int) ; 
 int /*<<< orphan*/  cblas_zsyrk (int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  oneD ; 
 int /*<<< orphan*/  oneF ; 
 int /*<<< orphan*/  zeroD ; 
 int /*<<< orphan*/  zeroF ; 

__attribute__((used)) static void
syrk(int typenum, enum CBLAS_ORDER order, enum CBLAS_TRANSPOSE trans,
     int n, int k,
     PyArrayObject *A, int lda, PyArrayObject *R)
{
    const void *Adata = PyArray_DATA(A);
    void *Rdata = PyArray_DATA(R);
    int ldc = PyArray_DIM(R, 1) > 1 ? PyArray_DIM(R, 1) : 1;

    npy_intp i;
    npy_intp j;

    switch (typenum) {
        case NPY_DOUBLE:
            cblas_dsyrk(order, CblasUpper, trans, n, k, 1.,
                        Adata, lda, 0., Rdata, ldc);

            for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    *((npy_double*)PyArray_GETPTR2(R, j, i)) =
                            *((npy_double*)PyArray_GETPTR2(R, i, j));
                }
            }
            break;
        case NPY_FLOAT:
            cblas_ssyrk(order, CblasUpper, trans, n, k, 1.f,
                        Adata, lda, 0.f, Rdata, ldc);

            for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    *((npy_float*)PyArray_GETPTR2(R, j, i)) =
                            *((npy_float*)PyArray_GETPTR2(R, i, j));
                }
            }
            break;
        case NPY_CDOUBLE:
            cblas_zsyrk(order, CblasUpper, trans, n, k, oneD,
                        Adata, lda, zeroD, Rdata, ldc);

            for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    *((npy_cdouble*)PyArray_GETPTR2(R, j, i)) =
                            *((npy_cdouble*)PyArray_GETPTR2(R, i, j));
                }
            }
            break;
        case NPY_CFLOAT:
            cblas_csyrk(order, CblasUpper, trans, n, k, oneF,
                        Adata, lda, zeroF, Rdata, ldc);

            for (i = 0; i < n; i++) {
                for (j = i + 1; j < n; j++) {
                    *((npy_cfloat*)PyArray_GETPTR2(R, j, i)) =
                            *((npy_cfloat*)PyArray_GETPTR2(R, i, j));
                }
            }
            break;
    }
}