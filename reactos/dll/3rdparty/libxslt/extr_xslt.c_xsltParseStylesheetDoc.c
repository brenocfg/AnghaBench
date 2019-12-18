#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
struct TYPE_6__ {int /*<<< orphan*/ * compCtxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_CCTXT (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltCompilationCtxtFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltInitGlobals () ; 
 TYPE_1__* xsltParseStylesheetImportedDoc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltResolveStylesheetAttributeSet (TYPE_1__*) ; 

xsltStylesheetPtr
xsltParseStylesheetDoc(xmlDocPtr doc) {
    xsltStylesheetPtr ret;

    xsltInitGlobals();

    ret = xsltParseStylesheetImportedDoc(doc, NULL);
    if (ret == NULL)
	return(NULL);

    xsltResolveStylesheetAttributeSet(ret);
#ifdef XSLT_REFACTORED
    /*
    * Free the compilation context.
    * TODO: Check if it's better to move this cleanup to
    *   xsltParseStylesheetImportedDoc().
    */
    if (ret->compCtxt != NULL) {
	xsltCompilationCtxtFree(XSLT_CCTXT(ret));
	ret->compCtxt = NULL;
    }
#endif
    return(ret);
}