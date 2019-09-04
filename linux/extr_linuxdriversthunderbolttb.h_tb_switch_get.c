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
struct tb_switch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct tb_switch *tb_switch_get(struct tb_switch *sw)
{
	if (sw)
		get_device(&sw->dev);
	return sw;
}