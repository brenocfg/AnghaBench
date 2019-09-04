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
 int EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIND_ZVAL_NULL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MAX_LENGTH_OF_DOUBLE ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_DVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  php_gcvt (int /*<<< orphan*/ ,int,char,char,char*) ; 
 int /*<<< orphan*/  precision ; 
 scalar_t__ safe_emalloc (int,int,scalar_t__) ; 
 int /*<<< orphan*/  set_ns_and_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNodeSetContentLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_get_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr to_xml_double(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	xmlNodePtr ret;
	zval tmp;
	char *str;

	ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	xmlAddChild(parent, ret);
	FIND_ZVAL_NULL(data, ret, style);

	ZVAL_DOUBLE(&tmp, zval_get_double(data));

	str = (char *) safe_emalloc(EG(precision) >= 0 ? EG(precision) : 17, 1, MAX_LENGTH_OF_DOUBLE + 1);
	php_gcvt(Z_DVAL(tmp), EG(precision), '.', 'E', str);
	xmlNodeSetContentLen(ret, BAD_CAST(str), strlen(str));
	efree(str);

	if (style == SOAP_ENCODED) {
		set_ns_and_type(ret, type);
	}
	return ret;
}