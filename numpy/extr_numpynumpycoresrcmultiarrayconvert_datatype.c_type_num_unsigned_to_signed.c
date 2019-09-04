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
 int NPY_BYTE ; 
 int NPY_INT ; 
 int NPY_LONG ; 
 int NPY_LONGLONG ; 
 int NPY_SHORT ; 
#define  NPY_UBYTE 132 
#define  NPY_UINT 131 
#define  NPY_ULONG 130 
#define  NPY_ULONGLONG 129 
#define  NPY_USHORT 128 

__attribute__((used)) static int
type_num_unsigned_to_signed(int type_num)
{
    switch (type_num) {
        case NPY_UBYTE:
            return NPY_BYTE;
        case NPY_USHORT:
            return NPY_SHORT;
        case NPY_UINT:
            return NPY_INT;
        case NPY_ULONG:
            return NPY_LONG;
        case NPY_ULONGLONG:
            return NPY_LONGLONG;
        default:
            return type_num;
    }
}