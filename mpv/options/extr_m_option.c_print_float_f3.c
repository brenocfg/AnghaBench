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
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 double VAL (void const*) ; 
 char* print_double_f3 (int /*<<< orphan*/  const*,double*) ; 

__attribute__((used)) static char *print_float_f3(const m_option_t *opt, const void *val)
{
    double tmp = VAL(val);
    return print_double_f3(opt, &tmp);
}