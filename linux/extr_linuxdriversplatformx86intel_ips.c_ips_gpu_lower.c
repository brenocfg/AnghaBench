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
struct ips_driver {int gpu_turbo_enabled; int /*<<< orphan*/  (* gpu_lower ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ips_gpu_turbo_enabled (struct ips_driver*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void ips_gpu_lower(struct ips_driver *ips)
{
	if (!ips_gpu_turbo_enabled(ips))
		return;

	if (!ips->gpu_lower())
		ips->gpu_turbo_enabled = false;

	return;
}