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
struct quat {float x; float y; float z; float w; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ obs_data_get_double (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void get_quat(obs_data_t *obj, struct quat *val)
{
	if (!obj)
		return;

	val->x = (float)obs_data_get_double(obj, "x");
	val->y = (float)obs_data_get_double(obj, "y");
	val->z = (float)obs_data_get_double(obj, "z");
	val->w = (float)obs_data_get_double(obj, "w");
	obs_data_release(obj);
}