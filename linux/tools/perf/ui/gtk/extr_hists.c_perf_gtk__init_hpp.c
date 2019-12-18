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
struct TYPE_2__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 size_t PERF_HPP__OVERHEAD ; 
 size_t PERF_HPP__OVERHEAD_ACC ; 
 size_t PERF_HPP__OVERHEAD_GUEST_SYS ; 
 size_t PERF_HPP__OVERHEAD_GUEST_US ; 
 size_t PERF_HPP__OVERHEAD_SYS ; 
 size_t PERF_HPP__OVERHEAD_US ; 
 int /*<<< orphan*/  perf_gtk__hpp_color_overhead ; 
 int /*<<< orphan*/  perf_gtk__hpp_color_overhead_acc ; 
 int /*<<< orphan*/  perf_gtk__hpp_color_overhead_guest_sys ; 
 int /*<<< orphan*/  perf_gtk__hpp_color_overhead_guest_us ; 
 int /*<<< orphan*/  perf_gtk__hpp_color_overhead_sys ; 
 int /*<<< orphan*/  perf_gtk__hpp_color_overhead_us ; 
 TYPE_1__* perf_hpp__format ; 

void perf_gtk__init_hpp(void)
{
	perf_hpp__format[PERF_HPP__OVERHEAD].color =
				perf_gtk__hpp_color_overhead;
	perf_hpp__format[PERF_HPP__OVERHEAD_SYS].color =
				perf_gtk__hpp_color_overhead_sys;
	perf_hpp__format[PERF_HPP__OVERHEAD_US].color =
				perf_gtk__hpp_color_overhead_us;
	perf_hpp__format[PERF_HPP__OVERHEAD_GUEST_SYS].color =
				perf_gtk__hpp_color_overhead_guest_sys;
	perf_hpp__format[PERF_HPP__OVERHEAD_GUEST_US].color =
				perf_gtk__hpp_color_overhead_guest_us;
	perf_hpp__format[PERF_HPP__OVERHEAD_ACC].color =
				perf_gtk__hpp_color_overhead_acc;
}