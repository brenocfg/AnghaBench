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
struct hist_entry {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ he_weight (struct hist_entry*) ; 

__attribute__((used)) static int64_t
sort__local_weight_cmp(struct hist_entry *left, struct hist_entry *right)
{
	return he_weight(left) - he_weight(right);
}