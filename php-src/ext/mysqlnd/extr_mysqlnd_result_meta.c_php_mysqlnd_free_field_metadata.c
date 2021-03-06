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
struct TYPE_3__ {scalar_t__ sname; int /*<<< orphan*/ * def; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ MYSQLND_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
php_mysqlnd_free_field_metadata(MYSQLND_FIELD *meta)
{
	if (meta) {
		meta->root = NULL;
		meta->def = NULL;
		if (meta->sname) {
			zend_string_release_ex(meta->sname, 0);
		}
	}
}