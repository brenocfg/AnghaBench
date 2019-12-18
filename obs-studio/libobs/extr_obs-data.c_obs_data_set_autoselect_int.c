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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_item_auto ; 

void obs_data_set_autoselect_int(obs_data_t *data, const char *name,
				 long long val)
{
	obs_set_int(data, NULL, name, val, set_item_auto);
}