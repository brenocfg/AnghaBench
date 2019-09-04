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

/* Variables and functions */
 scalar_t__ __init_state ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  init_preload () ; 

__attribute__((used)) static void try_init_preload(void)
{
	if (__init_state != done)
		init_preload();
}