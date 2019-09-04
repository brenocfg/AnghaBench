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
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  encodeTypePtr ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  FIND_ZVAL_NULL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_DOUBLE ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 double floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ns_and_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNodeSetContent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNodeSetContentLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_long_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_get_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr to_xml_long(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	xmlNodePtr ret;

	ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	xmlAddChild(parent, ret);
	FIND_ZVAL_NULL(data, ret, style);

	if (Z_TYPE_P(data) == IS_DOUBLE) {
		char s[256];

		snprintf(s, sizeof(s), "%0.0F",floor(Z_DVAL_P(data)));
		xmlNodeSetContent(ret, BAD_CAST(s));
	} else {
		zend_string *str = zend_long_to_str(zval_get_long(data));
		xmlNodeSetContentLen(ret, BAD_CAST(ZSTR_VAL(str)), ZSTR_LEN(str));
		zend_string_release_ex(str, 0);
	}

	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, type);
	}
	return ret;
}