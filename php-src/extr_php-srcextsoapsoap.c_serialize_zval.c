#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* sdlParamPtr ;
typedef  int /*<<< orphan*/ * encodePtr ;
struct TYPE_12__ {TYPE_1__* element; int /*<<< orphan*/ * encode; } ;
struct TYPE_11__ {scalar_t__ name; } ;
struct TYPE_10__ {int /*<<< orphan*/  def; int /*<<< orphan*/  nillable; int /*<<< orphan*/  fixed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 TYPE_2__* master_to_xml (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  xmlNodeSetName (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr serialize_zval(zval *val, sdlParamPtr param, char *paramName, int style, xmlNodePtr parent) /* {{{ */
{
	xmlNodePtr xmlParam;
	encodePtr enc;
	zval defval;

	ZVAL_UNDEF(&defval);
	if (param != NULL) {
		enc = param->encode;
		if (val == NULL) {
			if (param->element) {
				if (param->element->fixed) {
					ZVAL_STRING(&defval, param->element->fixed);
					val = &defval;
				} else if (param->element->def && !param->element->nillable) {
					ZVAL_STRING(&defval, param->element->def);
					val = &defval;
				}
			}
		}
	} else {
		enc = NULL;
	}
	xmlParam = master_to_xml(enc, val, style, parent);
	zval_ptr_dtor(&defval);
	if (!strcmp((char*)xmlParam->name, "BOGUS")) {
		xmlNodeSetName(xmlParam, BAD_CAST(paramName));
	}
	return xmlParam;
}