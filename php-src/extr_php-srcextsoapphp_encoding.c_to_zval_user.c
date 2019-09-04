#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlBufferPtr ;
typedef  TYPE_2__* encodeTypePtr ;
struct TYPE_5__ {TYPE_1__* map; } ;
struct TYPE_4__ {int /*<<< orphan*/  to_zval; } ;

/* Variables and functions */
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ FAILURE ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xmlBufferContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlCopyNode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlFreeNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNodeDump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

zval *to_zval_user(zval *ret, encodeTypePtr type, xmlNodePtr node)
{
	if (type && type->map && Z_TYPE(type->map->to_zval) != IS_UNDEF) {
		xmlBufferPtr buf;
		zval data;
		xmlNodePtr copy;

		copy = xmlCopyNode(node, 1);
		buf = xmlBufferCreate();
		xmlNodeDump(buf, NULL, copy, 0, 0);
		ZVAL_STRING(&data, (char*)xmlBufferContent(buf));
		xmlBufferFree(buf);
		xmlFreeNode(copy);

		if (call_user_function(NULL, NULL, &type->map->to_zval, ret, 1, &data) == FAILURE) {
			soap_error0(E_ERROR, "Encoding: Error calling from_xml callback");
		} else if (EG(exception)) {
			ZVAL_NULL(ret);
		}
		zval_ptr_dtor(&data);
	} else {
		ZVAL_NULL(ret);
	}
	return ret;
}