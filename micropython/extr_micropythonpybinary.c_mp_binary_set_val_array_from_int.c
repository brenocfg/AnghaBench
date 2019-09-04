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
typedef  size_t mp_uint_t ;
typedef  void* mp_int_t ;

/* Variables and functions */
#define  BYTEARRAY_TYPECODE 128 

void mp_binary_set_val_array_from_int(char typecode, void *p, mp_uint_t index, mp_int_t val) {
    switch (typecode) {
        case 'b':
            ((signed char*)p)[index] = val;
            break;
        case BYTEARRAY_TYPECODE:
        case 'B':
            ((unsigned char*)p)[index] = val;
            break;
        case 'h':
            ((short*)p)[index] = val;
            break;
        case 'H':
            ((unsigned short*)p)[index] = val;
            break;
        case 'i':
            ((int*)p)[index] = val;
            break;
        case 'I':
            ((unsigned int*)p)[index] = val;
            break;
        case 'l':
            ((long*)p)[index] = val;
            break;
        case 'L':
            ((unsigned long*)p)[index] = val;
            break;
        #if MICROPY_LONGINT_IMPL != MICROPY_LONGINT_IMPL_NONE
        case 'q':
            ((long long*)p)[index] = val;
            break;
        case 'Q':
            ((unsigned long long*)p)[index] = val;
            break;
        #endif
#if MICROPY_PY_BUILTINS_FLOAT
        case 'f':
            ((float*)p)[index] = val;
            break;
        case 'd':
            ((double*)p)[index] = val;
            break;
#endif
        // Extension to CPython: array of pointers
        case 'P':
            ((void**)p)[index] = (void*)(uintptr_t)val;
            break;
    }
}