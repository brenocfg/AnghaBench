#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* map; } ;
struct hist_entry {TYPE_2__ ms; } ;
struct dso {int dummy; } ;
struct TYPE_3__ {struct dso const* dso; } ;

/* Variables and functions */
 int HIST_FILTER__DSO ; 

__attribute__((used)) static int hist_entry__dso_filter(struct hist_entry *he, int type, const void *arg)
{
	const struct dso *dso = arg;

	if (type != HIST_FILTER__DSO)
		return -1;

	return dso && (!he->ms.map || he->ms.map->dso != dso);
}