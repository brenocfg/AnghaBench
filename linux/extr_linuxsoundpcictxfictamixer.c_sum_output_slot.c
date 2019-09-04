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
struct rsc {int dummy; } ;

/* Variables and functions */
 int sum_index (struct rsc const*) ; 

__attribute__((used)) static int sum_output_slot(const struct rsc *rsc)
{
	return (sum_index(rsc) << 4) + 0xc;
}