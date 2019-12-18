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
struct quat {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_set_obj ; 
 int /*<<< orphan*/  set_quat (int /*<<< orphan*/ *,char const*,struct quat const*,int /*<<< orphan*/ ) ; 

void obs_data_set_quat(obs_data_t *data, const char *name,
		       const struct quat *val)
{
	set_quat(data, name, val, obs_data_set_obj);
}