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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static mrb_value
mrb_f_sleep(mrb_state *mrb, mrb_value self)
{
    time_t beg = time(0);
    time_t end;
#ifndef MRB_WITHOUT_FLOAT
    mrb_float sec;

    mrb_get_args(mrb, "f", &sec);
    if (sec >= 0) {
        usleep(sec * 1000000);
    }
    else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "time interval must not be negative");
    }
#else
    mrb_int sec;

    mrb_get_args(mrb, "i", &sec);
    if (sec >= 0) {
        sleep(sec);
    } else {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "time interval must not be negative");
    }
#endif
    end = time(0) - beg;

    return mrb_fixnum_value(end);
}