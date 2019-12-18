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
typedef  int /*<<< orphan*/  zend_blacklist_entry ;
struct TYPE_3__ {int pos; int size; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ zend_blacklist ;

/* Variables and functions */
 scalar_t__ ZEND_BLACKLIST_BLOCK_SIZE ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void zend_accel_blacklist_allocate(zend_blacklist *blacklist)
{
	if (blacklist->pos == blacklist->size) {
		blacklist->size += ZEND_BLACKLIST_BLOCK_SIZE;
		blacklist->entries = (zend_blacklist_entry *) realloc(blacklist->entries, sizeof(zend_blacklist_entry)*blacklist->size);
	}
}