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
 void* npy_ma_str_array ; 
 void* npy_ma_str_array_finalize ; 
 void* npy_ma_str_array_prepare ; 
 void* npy_ma_str_array_wrap ; 
 void* npy_ma_str_axis1 ; 
 void* npy_ma_str_axis2 ; 
 void* npy_ma_str_copy ; 
 void* npy_ma_str_dtype ; 
 void* npy_ma_str_implementation ; 
 void* npy_ma_str_ndmin ; 
 void* npy_ma_str_order ; 
 void* npy_ma_str_ufunc ; 

__attribute__((used)) static int
intern_strings(void)
{
    npy_ma_str_array = PyUString_InternFromString("__array__");
    npy_ma_str_array_prepare = PyUString_InternFromString("__array_prepare__");
    npy_ma_str_array_wrap = PyUString_InternFromString("__array_wrap__");
    npy_ma_str_array_finalize = PyUString_InternFromString("__array_finalize__");
    npy_ma_str_ufunc = PyUString_InternFromString("__array_ufunc__");
    npy_ma_str_implementation = PyUString_InternFromString("_implementation");
    npy_ma_str_order = PyUString_InternFromString("order");
    npy_ma_str_copy = PyUString_InternFromString("copy");
    npy_ma_str_dtype = PyUString_InternFromString("dtype");
    npy_ma_str_ndmin = PyUString_InternFromString("ndmin");
    npy_ma_str_axis1 = PyUString_InternFromString("axis1");
    npy_ma_str_axis2 = PyUString_InternFromString("axis2");

    return npy_ma_str_array && npy_ma_str_array_prepare &&
           npy_ma_str_array_wrap && npy_ma_str_array_finalize &&
           npy_ma_str_ufunc && npy_ma_str_implementation &&
           npy_ma_str_order && npy_ma_str_copy && npy_ma_str_dtype &&
           npy_ma_str_ndmin && npy_ma_str_axis1 && npy_ma_str_axis2;
}