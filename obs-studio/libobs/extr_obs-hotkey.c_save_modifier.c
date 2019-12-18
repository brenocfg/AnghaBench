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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_set_bool (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static inline void save_modifier(uint32_t modifiers, obs_data_t *data,
				 const char *name, uint32_t flag)
{
	if ((modifiers & flag) == flag)
		obs_data_set_bool(data, name, true);
}