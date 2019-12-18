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
struct perf_config_set {int dummy; } ;

/* Variables and functions */
 int collect_config (char const*,char const*,struct perf_config_set*) ; 
 char const* config_file_name ; 

int perf_config_set__collect(struct perf_config_set *set, const char *file_name,
			     const char *var, const char *value)
{
	config_file_name = file_name;
	return collect_config(var, value, set);
}