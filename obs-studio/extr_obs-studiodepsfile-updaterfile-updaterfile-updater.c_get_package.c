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
 int /*<<< orphan*/  bfree (char*) ; 
 char* get_path (char const*,char const*) ; 
 int /*<<< orphan*/ * obs_data_create_from_json_file (char*) ; 

__attribute__((used)) static inline obs_data_t *get_package(const char *base_path, const char *file)
{
	char *full_path = get_path(base_path, file);
	obs_data_t *package = obs_data_create_from_json_file(full_path);
	bfree(full_path);
	return package;
}