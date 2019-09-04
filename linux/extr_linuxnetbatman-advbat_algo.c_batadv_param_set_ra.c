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
struct kernel_param {int dummy; } ;
struct batadv_algo_ops {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct batadv_algo_ops* batadv_algo_get (char*) ; 
 int param_set_copystring (char*,struct kernel_param const*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int batadv_param_set_ra(const char *val, const struct kernel_param *kp)
{
	struct batadv_algo_ops *bat_algo_ops;
	char *algo_name = (char *)val;
	size_t name_len = strlen(algo_name);

	if (name_len > 0 && algo_name[name_len - 1] == '\n')
		algo_name[name_len - 1] = '\0';

	bat_algo_ops = batadv_algo_get(algo_name);
	if (!bat_algo_ops) {
		pr_err("Routing algorithm '%s' is not supported\n", algo_name);
		return -EINVAL;
	}

	return param_set_copystring(algo_name, kp);
}