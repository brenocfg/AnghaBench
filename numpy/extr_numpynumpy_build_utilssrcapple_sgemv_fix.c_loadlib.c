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
typedef  int /*<<< orphan*/  fortran_sgemv_t ;
typedef  int /*<<< orphan*/  errormsg ;
typedef  int /*<<< orphan*/  cblas_sgemv_t ;
typedef  int /*<<< orphan*/  cblas_sgemm_t ;

/* Variables and functions */
 int AVX_and_10_9 ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int RTLD_FIRST ; 
 int RTLD_LOCAL ; 
 char* VECLIB_FILE ; 
 int /*<<< orphan*/ * accelerate_cblas_sgemm ; 
 int /*<<< orphan*/ * accelerate_cblas_sgemv ; 
 int /*<<< orphan*/ * accelerate_sgemv ; 
 int cpu_supports_avx () ; 
 int /*<<< orphan*/ * dlopen (char*,int) ; 
 scalar_t__ dlsym (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  unloadlib () ; 
 int using_mavericks () ; 
 int /*<<< orphan*/ * veclib ; 

__attribute__((used)) __attribute__((constructor))
static void loadlib()
/* automatically executed on module import */
{
    char errormsg[1024];
    int AVX, MAVERICKS;
    memset((void*)errormsg, 0, sizeof(errormsg));
    /* check if the CPU supports AVX */
    AVX = cpu_supports_avx();
    /* check if the OS is MacOS X Mavericks */
    MAVERICKS = using_mavericks();
    /* we need the workaround when the CPU supports
     * AVX and the OS version is Mavericks */
    AVX_and_10_9 = AVX && MAVERICKS;
    /* load vecLib */
    veclib = dlopen(VECLIB_FILE, RTLD_LOCAL | RTLD_FIRST);
    if (!veclib) {
        veclib = NULL;
        snprintf(errormsg, sizeof(errormsg),
                 "Failed to open vecLib from location '%s'.", VECLIB_FILE);
        Py_FatalError(errormsg); /* calls abort() and dumps core */
    }
    /* resolve Fortran SGEMV from Accelerate */
    accelerate_sgemv = (fortran_sgemv_t*) dlsym(veclib, "sgemv_");
    if (!accelerate_sgemv) {
        unloadlib();
        Py_FatalError("Failed to resolve symbol 'sgemv_'.");
    }
    /* resolve cblas_sgemv from Accelerate */
    accelerate_cblas_sgemv = (cblas_sgemv_t*) dlsym(veclib, "cblas_sgemv");
    if (!accelerate_cblas_sgemv) {
        unloadlib();
        Py_FatalError("Failed to resolve symbol 'cblas_sgemv'.");
    }
    /* resolve cblas_sgemm from Accelerate */
    accelerate_cblas_sgemm = (cblas_sgemm_t*) dlsym(veclib, "cblas_sgemm");
    if (!accelerate_cblas_sgemm) {
        unloadlib();
        Py_FatalError("Failed to resolve symbol 'cblas_sgemm'.");
    }
}