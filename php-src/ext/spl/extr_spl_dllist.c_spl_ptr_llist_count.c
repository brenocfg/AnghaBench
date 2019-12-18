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
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ spl_ptr_llist ;

/* Variables and functions */

__attribute__((used)) static zend_long spl_ptr_llist_count(spl_ptr_llist *llist) /* {{{ */
{
	return (zend_long)llist->count;
}