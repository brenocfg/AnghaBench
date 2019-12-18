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
struct fetch_type {scalar_t__ name; } ;

/* Variables and functions */
 char* DEFAULT_FETCH_TYPE_STR ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct fetch_type const* probe_fetch_types ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct fetch_type *find_fetch_type(const char *type)
{
	int i;

	if (!type)
		type = DEFAULT_FETCH_TYPE_STR;

	/* Special case: bitfield */
	if (*type == 'b') {
		unsigned long bs;

		type = strchr(type, '/');
		if (!type)
			goto fail;

		type++;
		if (kstrtoul(type, 0, &bs))
			goto fail;

		switch (bs) {
		case 8:
			return find_fetch_type("u8");
		case 16:
			return find_fetch_type("u16");
		case 32:
			return find_fetch_type("u32");
		case 64:
			return find_fetch_type("u64");
		default:
			goto fail;
		}
	}

	for (i = 0; probe_fetch_types[i].name; i++) {
		if (strcmp(type, probe_fetch_types[i].name) == 0)
			return &probe_fetch_types[i];
	}

fail:
	return NULL;
}