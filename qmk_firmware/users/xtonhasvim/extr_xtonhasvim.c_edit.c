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
 int /*<<< orphan*/  VIM_START ; 
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  vstate ; 

__attribute__((used)) static void edit(void) { vstate = VIM_START; layer_clear(); }