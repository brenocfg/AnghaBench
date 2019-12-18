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
struct TYPE_2__ {int /*<<< orphan*/  nr; int /*<<< orphan*/  files; } ;
struct perf_data {TYPE_1__ dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void perf_data__close_dir(struct perf_data *data)
{
	close_dir(data->dir.files, data->dir.nr);
}