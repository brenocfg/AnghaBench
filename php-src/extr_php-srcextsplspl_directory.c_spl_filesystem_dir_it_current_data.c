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
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ spl_filesystem_iterator ;

/* Variables and functions */

__attribute__((used)) static zval *spl_filesystem_dir_it_current_data(zend_object_iterator *iter)
{
	spl_filesystem_iterator *iterator = (spl_filesystem_iterator *)iter;

	return &iterator->current;
}