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
struct TYPE_3__ {scalar_t__ level; int idom; } ;
typedef  TYPE_1__ zend_basic_block ;

/* Variables and functions */

__attribute__((used)) static int dominates(zend_basic_block *blocks, int a, int b) /* {{{ */
{
	while (blocks[b].level > blocks[a].level) {
		b = blocks[b].idom;
	}
	return a == b;
}