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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int is_modified; int /*<<< orphan*/  flags; int /*<<< orphan*/  old_flags; scalar_t__ is_deleted; } ;
typedef  TYPE_1__ phar_entry_info ;

/* Variables and functions */
 int /*<<< orphan*/  PHAR_ENT_COMPRESSION_MASK ; 
 int ZEND_HASH_APPLY_KEEP ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_set_compression(zval *zv, void *argument) /* {{{ */
{
	phar_entry_info *entry = (phar_entry_info *)Z_PTR_P(zv);
	uint32_t compress = *(uint32_t *)argument;

	if (entry->is_deleted) {
		return ZEND_HASH_APPLY_KEEP;
	}

	entry->old_flags = entry->flags;
	entry->flags &= ~PHAR_ENT_COMPRESSION_MASK;
	entry->flags |= compress;
	entry->is_modified = 1;
	return ZEND_HASH_APPLY_KEEP;
}