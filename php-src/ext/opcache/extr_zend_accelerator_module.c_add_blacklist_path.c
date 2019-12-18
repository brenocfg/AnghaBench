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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  path_length; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ zend_blacklist_entry ;

/* Variables and functions */
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_blacklist_path(zend_blacklist_entry *p, zval *return_value)
{
	add_next_index_stringl(return_value, p->path, p->path_length);
	return 0;
}