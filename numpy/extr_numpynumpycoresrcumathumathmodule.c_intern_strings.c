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
 void* PyUString_InternFromString (char*) ; 
 char* UFUNC_PYVALS_NAME ; 
 void* npy_um_str_array_finalize ; 
 void* npy_um_str_array_prepare ; 
 void* npy_um_str_array_wrap ; 
 void* npy_um_str_axes ; 
 void* npy_um_str_axis ; 
 void* npy_um_str_casting ; 
 void* npy_um_str_dtype ; 
 void* npy_um_str_extobj ; 
 void* npy_um_str_keepdims ; 
 void* npy_um_str_order ; 
 void* npy_um_str_out ; 
 void* npy_um_str_pyvals_name ; 
 void* npy_um_str_sig ; 
 void* npy_um_str_signature ; 
 void* npy_um_str_subok ; 
 void* npy_um_str_ufunc ; 
 void* npy_um_str_where ; 

__attribute__((used)) static int
intern_strings(void)
{
    npy_um_str_out = PyUString_InternFromString("out");
    npy_um_str_where = PyUString_InternFromString("where");
    npy_um_str_axes = PyUString_InternFromString("axes");
    npy_um_str_axis = PyUString_InternFromString("axis");
    npy_um_str_keepdims = PyUString_InternFromString("keepdims");
    npy_um_str_casting = PyUString_InternFromString("casting");
    npy_um_str_order = PyUString_InternFromString("order");
    npy_um_str_dtype = PyUString_InternFromString("dtype");
    npy_um_str_subok = PyUString_InternFromString("subok");
    npy_um_str_signature = PyUString_InternFromString("signature");
    npy_um_str_sig = PyUString_InternFromString("sig");
    npy_um_str_extobj = PyUString_InternFromString("extobj");
    npy_um_str_array_prepare = PyUString_InternFromString("__array_prepare__");
    npy_um_str_array_wrap = PyUString_InternFromString("__array_wrap__");
    npy_um_str_array_finalize = PyUString_InternFromString("__array_finalize__");
    npy_um_str_ufunc = PyUString_InternFromString("__array_ufunc__");
    npy_um_str_pyvals_name = PyUString_InternFromString(UFUNC_PYVALS_NAME);

    return npy_um_str_out && npy_um_str_subok && npy_um_str_array_prepare &&
        npy_um_str_array_wrap && npy_um_str_array_finalize && npy_um_str_ufunc;
}