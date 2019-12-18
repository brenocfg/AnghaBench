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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_function ;

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlreader_open_fn ; 
 int /*<<< orphan*/  xmlreader_xml_fn ; 
 int /*<<< orphan*/ * zend_std_get_method (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static zend_function *xmlreader_get_method(zend_object **obj, zend_string *name, const zval *key)
{
	if (ZSTR_LEN(name) == sizeof("open") - 1
			&& (ZSTR_VAL(name)[0] == 'o' || ZSTR_VAL(name)[0] == 'O')
			&& (ZSTR_VAL(name)[1] == 'p' || ZSTR_VAL(name)[1] == 'P')
			&& (ZSTR_VAL(name)[2] == 'e' || ZSTR_VAL(name)[2] == 'E')
			&& (ZSTR_VAL(name)[3] == 'n' || ZSTR_VAL(name)[3] == 'N')) {
		return (zend_function*)&xmlreader_open_fn;
	} else if (ZSTR_LEN(name) == sizeof("xml") - 1
			&& (ZSTR_VAL(name)[0] == 'x' || ZSTR_VAL(name)[0] == 'X')
			&& (ZSTR_VAL(name)[1] == 'm' || ZSTR_VAL(name)[1] == 'M')
			&& (ZSTR_VAL(name)[2] == 'l' || ZSTR_VAL(name)[2] == 'L')) {
		return (zend_function*)&xmlreader_xml_fn;
	}
	return zend_std_get_method(obj, name, key);;
}