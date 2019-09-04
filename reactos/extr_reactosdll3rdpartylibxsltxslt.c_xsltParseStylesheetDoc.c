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
typedef  int /*<<< orphan*/ * xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;

/* Variables and functions */
 int /*<<< orphan*/  xsltInitGlobals () ; 
 int /*<<< orphan*/ * xsltParseStylesheetImportedDoc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltResolveStylesheetAttributeSet (int /*<<< orphan*/ *) ; 

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