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
struct trace_array {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void __trace_array_put(struct trace_array *this_tr)
{
	WARN_ON(!this_tr->ref);
	this_tr->ref--;
}