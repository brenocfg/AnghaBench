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
 int /*<<< orphan*/  get_quat (int /*<<< orphan*/ ,struct quat*) ; 
 int /*<<< orphan*/  obs_data_get_obj (int /*<<< orphan*/ *,char const*) ; 

void obs_data_get_quat(obs_data_t *data, const char *name, struct quat *val)
{
	get_quat(obs_data_get_obj(data, name), val);
}