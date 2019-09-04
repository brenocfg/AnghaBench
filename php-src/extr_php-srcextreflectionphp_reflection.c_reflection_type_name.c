#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ type_reference ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_3__* ZEND_TYPE_CE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_CE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* zend_get_type_by_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *reflection_type_name(type_reference *param) {
	if (ZEND_TYPE_IS_NAME(param->type)) {
		return zend_string_copy(ZEND_TYPE_NAME(param->type));
	} else if (ZEND_TYPE_IS_CE(param->type)) {
		return zend_string_copy(ZEND_TYPE_CE(param->type)->name);
	} else {
		char *name = zend_get_type_by_const(ZEND_TYPE_CODE(param->type));
		return zend_string_init(name, strlen(name), 0);
	}
}