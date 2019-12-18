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
struct TYPE_3__ {scalar_t__ alias; scalar_t__ name; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void php_openssl_add_method(const OBJ_NAME *name, void *arg) /* {{{ */
{
	if (name->alias == 0) {
		add_next_index_string((zval*)arg, (char*)name->name);
	}
}