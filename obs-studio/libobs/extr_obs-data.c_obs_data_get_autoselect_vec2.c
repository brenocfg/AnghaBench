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
struct vec2 {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_vec2 (int /*<<< orphan*/ ,struct vec2*) ; 
 int /*<<< orphan*/  obs_data_get_autoselect_obj (int /*<<< orphan*/ *,char const*) ; 

void obs_data_get_autoselect_vec2(obs_data_t *data, const char *name,
				  struct vec2 *val)
{
	get_vec2(obs_data_get_autoselect_obj(data, name), val);
}