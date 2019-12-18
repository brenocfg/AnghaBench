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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 unsigned int const M_FATAL ; 
 int fatal_error_triggered ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 

void
x_msg_va(const unsigned int flags, const char *format,
         va_list arglist)
{
    if (flags & M_FATAL)
    {
        fatal_error_triggered = true;
        printf("FATAL ERROR:");
    }
    vprintf(format, arglist);
    printf("\n");
}