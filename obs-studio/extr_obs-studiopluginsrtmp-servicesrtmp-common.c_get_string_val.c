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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_is_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char const*) ; 
 char const* json_string_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline const char *get_string_val(json_t *service, const char *key)
{
	json_t *str_val = json_object_get(service, key);
	if (!str_val || !json_is_string(str_val))
		return NULL;

	return json_string_value(str_val);
}