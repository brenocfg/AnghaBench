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
struct obs_module_path {void* data; void* bin; } ;
struct TYPE_2__ {int /*<<< orphan*/  module_paths; } ;

/* Variables and functions */
 void* bstrdup (char const*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct obs_module_path*) ; 
 TYPE_1__* obs ; 

void obs_add_module_path(const char *bin, const char *data)
{
	struct obs_module_path omp;

	if (!obs || !bin || !data)
		return;

	omp.bin = bstrdup(bin);
	omp.data = bstrdup(data);
	da_push_back(obs->module_paths, &omp);
}