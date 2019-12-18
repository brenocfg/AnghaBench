#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct syscall_arg {size_t idx; } ;
struct syscall {TYPE_1__* arg_fmt; } ;
struct TYPE_2__ {unsigned long (* mask_val ) (struct syscall_arg*,unsigned long) ;} ;

/* Variables and functions */
 unsigned long stub1 (struct syscall_arg*,unsigned long) ; 

__attribute__((used)) static unsigned long syscall__mask_val(struct syscall *sc, struct syscall_arg *arg, unsigned long val)
{
	if (sc->arg_fmt && sc->arg_fmt[arg->idx].mask_val)
		return sc->arg_fmt[arg->idx].mask_val(arg, val);

	return val;
}