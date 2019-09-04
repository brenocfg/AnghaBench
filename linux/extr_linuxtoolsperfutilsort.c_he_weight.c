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
typedef  int u64 ;
struct TYPE_2__ {int nr_events; int weight; } ;
struct hist_entry {TYPE_1__ stat; } ;

/* Variables and functions */

__attribute__((used)) static u64 he_weight(struct hist_entry *he)
{
	return he->stat.nr_events ? he->stat.weight / he->stat.nr_events : 0;
}