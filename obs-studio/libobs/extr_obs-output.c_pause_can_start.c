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
struct pause_data {int /*<<< orphan*/  ts_end; int /*<<< orphan*/  ts_start; } ;

/* Variables and functions */

__attribute__((used)) static inline bool pause_can_start(struct pause_data *pause)
{
	return !pause->ts_start && !pause->ts_end;
}