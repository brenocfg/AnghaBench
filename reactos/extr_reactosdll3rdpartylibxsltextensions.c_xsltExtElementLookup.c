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
typedef  int /*<<< orphan*/ * XML_CAST_FPTR ;
struct TYPE_3__ {int /*<<< orphan*/ * extElements; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlHashLookup2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xsltExtModuleElementLookup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xsltTransformFunction
xsltExtElementLookup(xsltTransformContextPtr ctxt,
                     const xmlChar * name, const xmlChar * URI)
{
    xsltTransformFunction ret;

    if ((name == NULL) || (URI == NULL))
        return (NULL);

    if ((ctxt != NULL) && (ctxt->extElements != NULL)) {
        XML_CAST_FPTR(ret) = xmlHashLookup2(ctxt->extElements, name, URI);
        if (ret != NULL) {
            return(ret);
        }
    }

    ret = xsltExtModuleElementLookup(name, URI);

    return (ret);
}