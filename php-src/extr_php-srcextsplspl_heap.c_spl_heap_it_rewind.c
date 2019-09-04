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
typedef  int /*<<< orphan*/  zend_object_iterator ;

/* Variables and functions */

__attribute__((used)) static void spl_heap_it_rewind(zend_object_iterator *iter) /* {{{ */
{
	/* do nothing, the iterator always points to the top element */
}