#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  spaces; } ;
typedef  TYPE_1__ RSpaces ;
typedef  TYPE_2__ RBIter ;

/* Variables and functions */
 TYPE_2__ r_rbtree_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool r_spaces_is_empty(RSpaces *sp) {
	RBIter it = r_rbtree_first (sp->spaces);
	return it.len == 0;
}