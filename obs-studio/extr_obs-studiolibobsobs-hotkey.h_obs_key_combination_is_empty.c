#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ key; int /*<<< orphan*/  modifiers; } ;
typedef  TYPE_1__ obs_key_combination_t ;

/* Variables and functions */
 scalar_t__ OBS_KEY_NONE ; 

__attribute__((used)) static inline bool obs_key_combination_is_empty(obs_key_combination_t combo)
{
	return !combo.modifiers && combo.key == OBS_KEY_NONE;
}