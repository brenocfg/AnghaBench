#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlXPathObjectPtr ;
typedef  TYPE_2__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/ * xmlBufferPtr ;
struct TYPE_8__ {int /*<<< orphan*/  node; } ;
struct TYPE_7__ {double floatval; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufferCCat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xmlBufferCat (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlBufferContent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ *) ; 
 TYPE_1__* xmlXPathEvalExpression (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_1__*) ; 

__attribute__((used)) static int
xsltNumberFormatGetValue(xmlXPathContextPtr context,
			 xmlNodePtr node,
			 const xmlChar *value,
			 double *number)
{
    int amount = 0;
    xmlBufferPtr pattern;
    xmlXPathObjectPtr obj;

    pattern = xmlBufferCreate();
    if (pattern != NULL) {
	xmlBufferCCat(pattern, "number(");
	xmlBufferCat(pattern, value);
	xmlBufferCCat(pattern, ")");
	context->node = node;
	obj = xmlXPathEvalExpression(xmlBufferContent(pattern),
				     context);
	if (obj != NULL) {
	    *number = obj->floatval;
	    amount++;
	    xmlXPathFreeObject(obj);
	}
	xmlBufferFree(pattern);
    }
    return amount;
}