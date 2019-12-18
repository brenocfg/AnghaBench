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
typedef  int /*<<< orphan*/  raw_u32 ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ CHECK (int,char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int* ERR_PTR (int /*<<< orphan*/ ) ; 
 int const NAME_TBD ; 
 int /*<<< orphan*/  free (int*) ; 
 char* get_next_str (char const*,char const*) ; 
 int get_raw_sec_size (int const*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static __u32 *patch_name_tbd(const __u32 *raw_u32,
			     const char *str, __u32 str_off,
			     unsigned int str_sec_size,
			     unsigned int *ret_size)
{
	int i, raw_u32_size = get_raw_sec_size(raw_u32);
	const char *end_str = str + str_sec_size;
	const char *next_str = str + str_off;
	__u32 *new_u32 = NULL;

	if (raw_u32_size == -1)
		return ERR_PTR(-EINVAL);

	if (!raw_u32_size) {
		*ret_size = 0;
		return NULL;
	}

	new_u32 = malloc(raw_u32_size);
	if (!new_u32)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < raw_u32_size / sizeof(raw_u32[0]); i++) {
		if (raw_u32[i] == NAME_TBD) {
			next_str = get_next_str(next_str, end_str);
			if (CHECK(!next_str, "Error in getting next_str\n")) {
				free(new_u32);
				return ERR_PTR(-EINVAL);
			}
			new_u32[i] = next_str - str;
			next_str += strlen(next_str);
		} else {
			new_u32[i] = raw_u32[i];
		}
	}

	*ret_size = raw_u32_size;
	return new_u32;
}