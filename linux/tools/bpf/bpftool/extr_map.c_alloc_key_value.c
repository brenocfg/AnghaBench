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
struct bpf_map_info {scalar_t__ value_size; scalar_t__ key_size; } ;

/* Variables and functions */
 void* alloc_value (struct bpf_map_info*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  p_err (char*) ; 

__attribute__((used)) static int alloc_key_value(struct bpf_map_info *info, void **key, void **value)
{
	*key = NULL;
	*value = NULL;

	if (info->key_size) {
		*key = malloc(info->key_size);
		if (!*key) {
			p_err("key mem alloc failed");
			return -1;
		}
	}

	if (info->value_size) {
		*value = alloc_value(info);
		if (!*value) {
			p_err("value mem alloc failed");
			free(*key);
			*key = NULL;
			return -1;
		}
	}

	return 0;
}