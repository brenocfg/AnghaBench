#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/ * xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_11__ {TYPE_2__* xpathCtxt; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  dict; int /*<<< orphan*/ * doc; } ;
struct TYPE_9__ {int /*<<< orphan*/  dict; int /*<<< orphan*/ * doc; } ;

/* Variables and functions */
 TYPE_7__* XSLT_CCTXT (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlXPathCtxtCompile (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlXPathFreeContext (TYPE_2__*) ; 
 TYPE_2__* xmlXPathNewContext (int /*<<< orphan*/ *) ; 

xmlXPathCompExprPtr
xsltXPathCompileFlags(xsltStylesheetPtr style, const xmlChar *str, int flags) {
    xmlXPathContextPtr xpathCtxt;
    xmlXPathCompExprPtr ret;

    if (style != NULL) {
#ifdef XSLT_REFACTORED_XPATHCOMP
	if (XSLT_CCTXT(style)) {
	    /*
	    * Proposed by Jerome Pesenti
	    * --------------------------
	    * For better efficiency we'll reuse the compilation
	    * context's XPath context. For the common stylesheet using
	    * XPath expressions this will reduce compilation time to
	    * about 50%.
	    *
	    * See http://mail.gnome.org/archives/xslt/2006-April/msg00037.html
	    */
	    xpathCtxt = XSLT_CCTXT(style)->xpathCtxt;
	    xpathCtxt->doc = style->doc;
	} else
	    xpathCtxt = xmlXPathNewContext(style->doc);
#else
	xpathCtxt = xmlXPathNewContext(style->doc);
#endif
	if (xpathCtxt == NULL)
	    return NULL;
	xpathCtxt->dict = style->dict;
    } else {
	xpathCtxt = xmlXPathNewContext(NULL);
	if (xpathCtxt == NULL)
	    return NULL;
    }
    xpathCtxt->flags = flags;

    /*
    * Compile the expression.
    */
    ret = xmlXPathCtxtCompile(xpathCtxt, str);

#ifdef XSLT_REFACTORED_XPATHCOMP
    if ((style == NULL) || (! XSLT_CCTXT(style))) {
	xmlXPathFreeContext(xpathCtxt);
    }
#else
    xmlXPathFreeContext(xpathCtxt);
#endif
    /*
     * TODO: there is a lot of optimizations which should be possible
     *       like variable slot precomputations, function precomputations, etc.
     */

    return(ret);
}