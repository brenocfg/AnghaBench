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
 char* obs_data_get_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline const char *get_string_or_null(obs_data_t *settings,
					     const char *name)
{
	const char *value = obs_data_get_string(settings, name);
	if (!value || !strlen(value))
		return NULL;
	return value;
}