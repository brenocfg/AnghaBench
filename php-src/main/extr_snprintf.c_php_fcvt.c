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
 char* __cvt (double,int,int*,int*,int,int) ; 

__attribute__((used)) static inline char *php_fcvt(double value, int ndigit, int *decpt, int *sign) /* {{{ */
{
    return(__cvt(value, ndigit, decpt, sign, 1, 1));
}