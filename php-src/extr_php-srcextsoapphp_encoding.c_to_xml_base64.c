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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  FIND_ZVAL_NULL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_STRING ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_base64_encode (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ns_and_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewTextLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string_func (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr to_xml_base64(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	xmlNodePtr ret, text;
	zend_string *str;

	ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	xmlAddChild(parent, ret);
	FIND_ZVAL_NULL(data, ret, style);

	if (Z_TYPE_P(data) == IS_STRING) {
		str = php_base64_encode((unsigned char*)Z_STRVAL_P(data), Z_STRLEN_P(data));
	} else {
		zend_string *tmp = zval_get_string_func(data);
		str = php_base64_encode((unsigned char*) ZSTR_VAL(tmp), ZSTR_LEN(tmp));
		zend_string_release_ex(tmp, 0);
	}

	text = xmlNewTextLen(BAD_CAST(ZSTR_VAL(str)), ZSTR_LEN(str));
	xmlAddChild(ret, text);
	zend_string_release_ex(str, 0);

	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, type);
	}
	return ret;
}