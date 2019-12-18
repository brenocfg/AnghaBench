#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int __u8 ;
struct TYPE_2__ {char* prefix; int name_index; } ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int*) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  memcmp (char const*,char*,size_t) ; 
 TYPE_1__* prefix_tbl ; 
 size_t strlen (char*) ; 

const char *ext4_extract_xattr_name(const char *full_name, size_t full_name_len,
			      __u8 *name_index, size_t *name_len,
			      BOOL *found)
{
	int i;
	ASSERT(name_index);
	ASSERT(found);

	*found = FALSE;

	if (!full_name_len) {
		if (name_len)
			*name_len = 0;

		return NULL;
	}

	for (i = 0; prefix_tbl[i].prefix; i++) {
		size_t prefix_len = strlen(prefix_tbl[i].prefix);
		if (full_name_len >= prefix_len &&
		    !memcmp(full_name, prefix_tbl[i].prefix, prefix_len)) {
			BOOL require_name =
				prefix_tbl[i].prefix[prefix_len - 1] == '.';
			*name_index = prefix_tbl[i].name_index;
			if (name_len)
				*name_len = full_name_len - prefix_len;

			if (!(full_name_len - prefix_len) && require_name)
				return NULL;

			*found = TRUE;
			if (require_name)
				return full_name + prefix_len;

			return NULL;
		}
	}
	if (name_len)
		*name_len = 0;

	return NULL;
}