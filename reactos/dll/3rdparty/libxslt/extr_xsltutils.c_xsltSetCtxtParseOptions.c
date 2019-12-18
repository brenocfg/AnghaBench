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
typedef  TYPE_1__* xsltTransformContextPtr ;
struct TYPE_3__ {int parserOptions; int xinclude; } ;

/* Variables and functions */
 int XML_PARSE_XINCLUDE ; 

int
xsltSetCtxtParseOptions(xsltTransformContextPtr ctxt, int options)
{
    int oldopts;

    if (ctxt == NULL)
        return(-1);
    oldopts = ctxt->parserOptions;
    if (ctxt->xinclude)
        oldopts |= XML_PARSE_XINCLUDE;
    ctxt->parserOptions = options;
    if (options & XML_PARSE_XINCLUDE)
        ctxt->xinclude = 1;
    else
        ctxt->xinclude = 0;
    return(oldopts);
}