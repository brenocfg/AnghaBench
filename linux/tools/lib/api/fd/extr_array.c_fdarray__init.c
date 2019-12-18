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
struct fdarray {int nr_autogrow; scalar_t__ nr_alloc; scalar_t__ nr; int /*<<< orphan*/ * priv; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */

void fdarray__init(struct fdarray *fda, int nr_autogrow)
{
	fda->entries	 = NULL;
	fda->priv	 = NULL;
	fda->nr		 = fda->nr_alloc = 0;
	fda->nr_autogrow = nr_autogrow;
}