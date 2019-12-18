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
 int /*<<< orphan*/  json_is_boolean (int /*<<< orphan*/ *) ; 
 int json_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline bool get_bool_val(json_t *service, const char *key)
{
	json_t *bool_val = json_object_get(service, key);
	if (!bool_val || !json_is_boolean(bool_val))
		return false;

	return json_is_true(bool_val);
}