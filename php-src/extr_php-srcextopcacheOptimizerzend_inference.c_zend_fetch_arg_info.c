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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_script ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_arg_info ;
typedef  int uint32_t ;

/* Variables and functions */
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 scalar_t__ ZEND_TYPE_ALLOW_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_TYPE_IS_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_class_entry (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int zend_convert_type_code_to_may_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t zend_fetch_arg_info(const zend_script *script, zend_arg_info *arg_info, zend_class_entry **pce)
{
	uint32_t tmp = 0;

	*pce = NULL;
	if (ZEND_TYPE_IS_CLASS(arg_info->type)) {
		// class type hinting...
		zend_string *lcname = zend_string_tolower(ZEND_TYPE_NAME(arg_info->type));
		tmp |= MAY_BE_OBJECT;
		*pce = get_class_entry(script, lcname);
		zend_string_release_ex(lcname, 0);
	} else if (ZEND_TYPE_IS_CODE(arg_info->type)) {
		tmp |= zend_convert_type_code_to_may_be(ZEND_TYPE_CODE(arg_info->type));
	} else {
		tmp |= MAY_BE_ANY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
	}
	if (ZEND_TYPE_ALLOW_NULL(arg_info->type)) {
		tmp |= MAY_BE_NULL;
	}
	return tmp;
}