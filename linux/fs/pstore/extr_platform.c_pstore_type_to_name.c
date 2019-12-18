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
typedef  enum pstore_type_id { ____Placeholder_pstore_type_id } pstore_type_id ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ PSTORE_TYPE_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 char const** pstore_type_names ; 

const char *pstore_type_to_name(enum pstore_type_id type)
{
	BUILD_BUG_ON(ARRAY_SIZE(pstore_type_names) != PSTORE_TYPE_MAX);

	if (WARN_ON_ONCE(type >= PSTORE_TYPE_MAX))
		return "unknown";

	return pstore_type_names[type];
}