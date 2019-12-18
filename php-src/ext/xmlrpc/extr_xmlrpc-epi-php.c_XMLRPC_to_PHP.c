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
typedef  int XMLRPC_VALUE_TYPE ;
typedef  scalar_t__ XMLRPC_VALUE ;

/* Variables and functions */
 char* XMLRPC_GetValueBase64 (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueBoolean (scalar_t__) ; 
 char const* XMLRPC_GetValueDateTime_ISO8601 (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueDouble (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueID (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueInt (scalar_t__) ; 
 char* XMLRPC_GetValueString (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_GetValueStringLen (scalar_t__) ; 
 int XMLRPC_GetValueType (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorNext (scalar_t__) ; 
 scalar_t__ XMLRPC_VectorRewind (scalar_t__) ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_zval_xmlrpc_type (int /*<<< orphan*/ *,int) ; 
#define  xmlrpc_base64 135 
#define  xmlrpc_boolean 134 
#define  xmlrpc_datetime 133 
#define  xmlrpc_double 132 
#define  xmlrpc_empty 131 
#define  xmlrpc_int 130 
#define  xmlrpc_string 129 
#define  xmlrpc_vector 128 

__attribute__((used)) static void XMLRPC_to_PHP(XMLRPC_VALUE el, zval *elem)
{
	const char* pStr;

	if (el) {
		XMLRPC_VALUE_TYPE type = XMLRPC_GetValueType(el);

		switch (type) {
			case xmlrpc_empty:
				ZVAL_NULL(elem);
				break;
			case xmlrpc_string:
				pStr = XMLRPC_GetValueString(el);
				if (pStr) {
					ZVAL_STRINGL(elem, pStr, XMLRPC_GetValueStringLen(el));
				}
				break;
			case xmlrpc_int:
				ZVAL_LONG(elem, XMLRPC_GetValueInt(el));
				break;
			case xmlrpc_boolean:
				ZVAL_BOOL(elem, XMLRPC_GetValueBoolean(el));
				break;
			case xmlrpc_double:
				ZVAL_DOUBLE(elem, XMLRPC_GetValueDouble(el));
				break;
			case xmlrpc_datetime:
				ZVAL_STRINGL(elem, XMLRPC_GetValueDateTime_ISO8601(el), XMLRPC_GetValueStringLen(el));
				break;
			case xmlrpc_base64:
				pStr = XMLRPC_GetValueBase64(el);
				if (pStr) {
					ZVAL_STRINGL(elem, pStr, XMLRPC_GetValueStringLen(el));
				}
				break;
			case xmlrpc_vector:
				array_init(elem);
				{
					XMLRPC_VALUE xIter = XMLRPC_VectorRewind(el);

					while( xIter ) {
						zval val;
						ZVAL_UNDEF(&val);
						XMLRPC_to_PHP(xIter, &val);
						if (!Z_ISUNDEF(val)) {
							add_zval(elem, XMLRPC_GetValueID(xIter), &val);
						}
						xIter = XMLRPC_VectorNext(el);
					}
				}
				break;
			default:
				break;
		}
		set_zval_xmlrpc_type(elem, type);
	}
}