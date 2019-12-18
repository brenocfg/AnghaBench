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
struct TYPE_2__ {scalar_t__ weight; } ;
struct hist_entry {TYPE_1__ stat; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t
sort__global_weight_cmp(struct hist_entry *left, struct hist_entry *right)
{
	return left->stat.weight - right->stat.weight;
}