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
 scalar_t__ json_integer_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline int get_int_val(json_t *service, const char *key)
{
	json_t *integer_val = json_object_get(service, key);
	if (!integer_val || !json_is_integer(integer_val))
		return 0;

	return (int)json_integer_value(integer_val);
}