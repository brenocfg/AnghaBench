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
struct i2s_dai {int mode; } ;

/* Variables and functions */
 int DAI_MANAGER ; 
 scalar_t__ is_opened (struct i2s_dai*) ; 

__attribute__((used)) static inline bool is_manager(struct i2s_dai *i2s)
{
	if (is_opened(i2s) && (i2s->mode & DAI_MANAGER))
		return true;
	else
		return false;
}