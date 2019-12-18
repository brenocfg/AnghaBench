#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ ht_iter; } ;
typedef  TYPE_1__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * spl_array_get_hash_table (TYPE_1__*) ; 
 int /*<<< orphan*/  spl_array_get_pos_ptr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  spl_array_skip_protected (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_internal_pointer_reset_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spl_array_rewind(spl_array_object *intern) /* {{{ */
{
	HashTable *aht = spl_array_get_hash_table(intern);

	if (intern->ht_iter == (uint32_t)-1) {
		spl_array_get_pos_ptr(aht, intern);
	} else {
		zend_hash_internal_pointer_reset_ex(aht, spl_array_get_pos_ptr(aht, intern));
		spl_array_skip_protected(intern, aht);
	}
}