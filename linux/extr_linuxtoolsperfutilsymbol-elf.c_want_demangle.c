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
struct TYPE_2__ {int demangle_kernel; int demangle; } ;

/* Variables and functions */
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static bool want_demangle(bool is_kernel_sym)
{
	return is_kernel_sym ? symbol_conf.demangle_kernel : symbol_conf.demangle;
}