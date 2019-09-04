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
typedef  struct kconf_id {int /*<<< orphan*/  name; } const kconf_id ;

/* Variables and functions */
 int KCONF_ID_ARRAY_SIZE ; 
 struct kconf_id const* kconf_id_array ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct kconf_id *kconf_id_lookup(register const char *str, register unsigned int len)
{
	int i;

	for (i = 0; i < KCONF_ID_ARRAY_SIZE; i++) {
		struct kconf_id *id = kconf_id_array+i;
		int l = strlen(id->name);

		if (len == l && !memcmp(str, id->name, len))
			return id;
	}
	return NULL;
}