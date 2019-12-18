#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ arg; } ;
typedef  TYPE_1__ exarg_T ;

/* Variables and functions */
 scalar_t__ ensure_ruby_initialized () ; 
 int /*<<< orphan*/  error_print (int) ; 
 int /*<<< orphan*/  rb_load_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rb_str_new2 (char*) ; 

void ex_rubyfile(exarg_T *eap)
{
    int state;

    if (ensure_ruby_initialized())
    {
	rb_load_protect(rb_str_new2((char *) eap->arg), 0, &state);
	if (state) error_print(state);
    }
}