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
struct sh_pfc {int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8a7795es1 ; 
 int /*<<< orphan*/  r8a7795es1_pinmux_info ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r8a7795_pinmux_init(struct sh_pfc *pfc)
{
	if (soc_device_match(r8a7795es1))
		pfc->info = &r8a7795es1_pinmux_info;

	return 0;
}