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
 int /*<<< orphan*/  NPY_CPU_BIG ; 
 int /*<<< orphan*/  PyArray_GetEndianness () ; 

__attribute__((used)) static char _normalize_byteorder(char byteorder)
{
    switch(byteorder) {
        case '=':
            if (PyArray_GetEndianness() == NPY_CPU_BIG) {
                return '>';
            }
            else {
                return '<';
            }
        default:
            return byteorder;
    }
}