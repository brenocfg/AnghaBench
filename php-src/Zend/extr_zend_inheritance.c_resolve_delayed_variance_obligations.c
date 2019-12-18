#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
struct TYPE_3__ {int /*<<< orphan*/  ce_flags; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ * CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ACC_LINKED ; 
 int /*<<< orphan*/  ZEND_ACC_UNRESOLVED_VARIANCE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_variance_obligation ; 
 int /*<<< orphan*/  delayed_variance_obligations ; 
 int /*<<< orphan*/  zend_hash_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_index_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resolve_delayed_variance_obligations(zend_class_entry *ce) {
	HashTable *all_obligations = CG(delayed_variance_obligations), *obligations;
	zend_ulong num_key = (zend_ulong) (uintptr_t) ce;

	ZEND_ASSERT(all_obligations != NULL);
	obligations = zend_hash_index_find_ptr(all_obligations, num_key);
	ZEND_ASSERT(obligations != NULL);

	zend_hash_apply(obligations, check_variance_obligation);
	if (zend_hash_num_elements(obligations) == 0) {
		ce->ce_flags &= ~ZEND_ACC_UNRESOLVED_VARIANCE;
		ce->ce_flags |= ZEND_ACC_LINKED;
		zend_hash_index_del(all_obligations, num_key);
	}
}