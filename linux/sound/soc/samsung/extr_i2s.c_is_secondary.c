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
struct i2s_dai {TYPE_1__* drv; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ SAMSUNG_I2S_ID_SECONDARY ; 

__attribute__((used)) static inline bool is_secondary(struct i2s_dai *i2s)
{
	return i2s->drv->id == SAMSUNG_I2S_ID_SECONDARY;
}