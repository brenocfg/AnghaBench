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
struct TYPE_2__ {scalar_t__ anticheat_hook; } ;
struct game_capture {int /*<<< orphan*/  is_app; TYPE_1__ config; } ;

/* Variables and functions */

__attribute__((used)) static inline bool use_anticheat(struct game_capture *gc)
{
	return gc->config.anticheat_hook && !gc->is_app;
}