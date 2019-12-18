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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * spl_array_get_pos_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ spl_array_is_object (int /*<<< orphan*/ *) ; 
 int spl_array_skip_protected (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_hash_has_more_elements_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_move_forward_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_array_next_ex(spl_array_object *intern, HashTable *aht) /* {{{ */
{
	uint32_t *pos_ptr = spl_array_get_pos_ptr(aht, intern);

	zend_hash_move_forward_ex(aht, pos_ptr);
	if (spl_array_is_object(intern)) {
		return spl_array_skip_protected(intern, aht);
	} else {
		return zend_hash_has_more_elements_ex(aht, pos_ptr);
	}
}