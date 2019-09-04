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
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */
 int ZEND_HASH_APPLY_KEEP ; 

__attribute__((used)) static int spl_iterator_count_apply(zend_object_iterator *iter, void *puser) /* {{{ */
{
	(*(zend_long*)puser)++;
	return ZEND_HASH_APPLY_KEEP;
}