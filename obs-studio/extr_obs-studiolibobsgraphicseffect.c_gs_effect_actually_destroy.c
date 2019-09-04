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
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  effect_free (int /*<<< orphan*/ *) ; 

void gs_effect_actually_destroy(gs_effect_t *effect)
{
	effect_free(effect);
	bfree(effect);
}