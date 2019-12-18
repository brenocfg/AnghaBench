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
struct TYPE_3__ {int /*<<< orphan*/  stack; scalar_t__ visited; } ;
typedef  TYPE_1__ zend_worklist ;
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  scalar_t__ zend_bitset ;
typedef  int /*<<< orphan*/  zend_arena ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ zend_arena_calloc (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_bitset_len (int) ; 
 int zend_worklist_stack_prepare (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int zend_worklist_prepare(zend_arena **arena, zend_worklist *worklist, int len)
{
	ZEND_ASSERT(len >= 0);
	worklist->visited = (zend_bitset)zend_arena_calloc(arena, sizeof(zend_ulong), zend_bitset_len(len));
	return zend_worklist_stack_prepare(arena, &worklist->stack, len);
}