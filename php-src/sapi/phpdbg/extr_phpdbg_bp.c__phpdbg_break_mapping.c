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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 size_t PHPDBG_BREAK_MAP ; 
 int /*<<< orphan*/ * PHPDBG_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/  zend_hash_index_update_ptr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _phpdbg_break_mapping(int id, HashTable *table) /* {{{ */
{
	zend_hash_index_update_ptr(&PHPDBG_G(bp)[PHPDBG_BREAK_MAP], id, table);
}