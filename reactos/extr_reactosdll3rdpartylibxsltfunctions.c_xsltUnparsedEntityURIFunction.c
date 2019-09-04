#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlXPathParserContextPtr ;
typedef  TYPE_3__* xmlXPathObjectPtr ;
typedef  TYPE_4__* xmlEntityPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {int /*<<< orphan*/  const* URI; } ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/ * stringval; } ;
struct TYPE_14__ {TYPE_1__* context; int /*<<< orphan*/  error; int /*<<< orphan*/ * value; } ;
struct TYPE_13__ {int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPATH_INVALID_ARITY ; 
 scalar_t__ XPATH_STRING ; 
 TYPE_3__* valuePop (TYPE_2__*) ; 
 int /*<<< orphan*/  valuePush (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* xmlGetDocEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* xmlXPathConvertString (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlXPathNewString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 

void
xsltUnparsedEntityURIFunction(xmlXPathParserContextPtr ctxt, int nargs){
    xmlXPathObjectPtr obj;
    xmlChar *str;

    if ((nargs != 1) || (ctxt->value == NULL)) {
        xsltGenericError(xsltGenericErrorContext,
		"unparsed-entity-uri() : expects one string arg\n");
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }
    obj = valuePop(ctxt);
    if (obj->type != XPATH_STRING) {
	obj = xmlXPathConvertString(obj);
    }

    str = obj->stringval;
    if (str == NULL) {
	valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
    } else {
	xmlEntityPtr entity;

	entity = xmlGetDocEntity(ctxt->context->doc, str);
	if (entity == NULL) {
	    valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
	} else {
	    if (entity->URI != NULL)
		valuePush(ctxt, xmlXPathNewString(entity->URI));
	    else
		valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
	}
    }
    xmlXPathFreeObject(obj);
}