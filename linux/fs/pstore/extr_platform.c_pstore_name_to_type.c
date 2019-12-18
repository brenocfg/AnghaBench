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
 int PSTORE_TYPE_MAX ; 
 int /*<<< orphan*/ * pstore_type_names ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

enum pstore_type_id pstore_name_to_type(const char *name)
{
	int i;

	for (i = 0; i < PSTORE_TYPE_MAX; i++) {
		if (!strcmp(pstore_type_names[i], name))
			return i;
	}

	return PSTORE_TYPE_MAX;
}