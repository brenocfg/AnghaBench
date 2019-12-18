#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformFunction ;
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_3__ {int /*<<< orphan*/ * extElements; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CAST_FPTR (int /*<<< orphan*/ *) ; 
 int xmlHashAddEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 

int
xsltRegisterExtElement(xsltTransformContextPtr ctxt, const xmlChar * name,
                       const xmlChar * URI, xsltTransformFunction function)
{
    if ((ctxt == NULL) || (name == NULL) ||
        (URI == NULL) || (function == NULL))
        return (-1);
    if (ctxt->extElements == NULL)
        ctxt->extElements = xmlHashCreate(10);
    if (ctxt->extElements == NULL)
        return (-1);
    return (xmlHashAddEntry2
            (ctxt->extElements, name, URI, XML_CAST_FPTR(function)));
}