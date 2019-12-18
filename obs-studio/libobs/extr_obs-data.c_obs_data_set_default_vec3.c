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
struct vec3 {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_set_default_obj ; 
 int /*<<< orphan*/  set_vec3 (int /*<<< orphan*/ *,char const*,struct vec3 const*,int /*<<< orphan*/ ) ; 

void obs_data_set_default_vec3(obs_data_t *data, const char *name,
			       const struct vec3 *val)
{
	set_vec3(data, name, val, obs_data_set_default_obj);
}