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
struct perf_hpp {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_hpp (struct perf_hpp*,int) ; 

__attribute__((used)) static int advance_hpp_check(struct perf_hpp *hpp, int inc)
{
	advance_hpp(hpp, inc);
	return hpp->size <= 0;
}