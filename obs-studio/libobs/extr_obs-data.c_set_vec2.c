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
struct vec2 {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  (* set_obj_t ) (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_double (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_vec2(obs_data_t *data, const char *name,
			    const struct vec2 *val, set_obj_t set_obj)
{
	obs_data_t *obj = obs_data_create();
	obs_data_set_double(obj, "x", val->x);
	obs_data_set_double(obj, "y", val->y);
	set_obj(data, name, obj);
	obs_data_release(obj);
}