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
typedef  int /*<<< orphan*/ * sdlTypePtr ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void make_persistent_sdl_type_ref(sdlTypePtr *type, HashTable *ptr_map, HashTable *bp_types)
{
	sdlTypePtr tmp;

	if ((tmp = zend_hash_str_find_ptr(ptr_map, (char *)type, sizeof(sdlTypePtr))) != NULL) {
		*type = tmp;
	} else {
		zend_hash_next_index_insert_ptr(bp_types, *type);
	}
}