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
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  FIND_ZVAL_NULL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_STRING ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 scalar_t__* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (unsigned char*) ; 
 scalar_t__ safe_emalloc (int,int,int) ; 
 int /*<<< orphan*/  set_ns_and_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewTextLen (unsigned char*,int) ; 
 int /*<<< orphan*/  zval_get_string_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr to_xml_hexbin(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	static char hexconvtab[] = "0123456789ABCDEF";
	xmlNodePtr ret, text;
	unsigned char *str;
	zval tmp;
	size_t i, j;

	ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	xmlAddChild(parent, ret);
	FIND_ZVAL_NULL(data, ret, style);

	if (Z_TYPE_P(data) != IS_STRING) {
		ZVAL_STR(&tmp, zval_get_string_func(data));
		data = &tmp;
	}
	str = (unsigned char *) safe_emalloc(Z_STRLEN_P(data) * 2, sizeof(char), 1);

	for (i = j = 0; i < Z_STRLEN_P(data); i++) {
		str[j++] = hexconvtab[((unsigned char)Z_STRVAL_P(data)[i]) >> 4];
		str[j++] = hexconvtab[((unsigned char)Z_STRVAL_P(data)[i]) & 15];
	}
	str[j] = '\0';

	text = xmlNewTextLen(str, Z_STRLEN_P(data) * 2 * sizeof(char));
	xmlAddChild(ret, text);
	efree(str);
	if (data == &tmp) {
		zval_ptr_dtor_str(&tmp);
	}

	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, type);
	}
	return ret;
}