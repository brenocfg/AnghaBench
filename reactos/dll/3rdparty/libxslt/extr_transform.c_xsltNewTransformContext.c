#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xsltTransformContext ;
typedef  int /*<<< orphan*/  xsltTemplatePtr ;
typedef  TYPE_3__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xsltStackElemPtr ;
typedef  TYPE_4__* xsltRuntimeExtraPtr ;
typedef  int /*<<< orphan*/  xsltRuntimeExtra ;
typedef  TYPE_5__* xsltDocumentPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  scalar_t__ xmlDocPtr ;
struct TYPE_23__ {int main; } ;
struct TYPE_19__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_22__ {TYPE_1__ val; int /*<<< orphan*/ * deallocate; int /*<<< orphan*/ * info; } ;
struct TYPE_21__ {scalar_t__ extrasNr; int /*<<< orphan*/  nsHash; scalar_t__ internalized; int /*<<< orphan*/  dict; } ;
struct TYPE_20__ {int internalized; int templMax; int varsMax; int extrasMax; int extrasNr; unsigned long* traceCode; scalar_t__ keyInitLevel; int /*<<< orphan*/  xinclude; scalar_t__ debugStatus; int /*<<< orphan*/  sec; int /*<<< orphan*/ * outputFile; int /*<<< orphan*/ * inst; TYPE_5__* document; int /*<<< orphan*/  parserOptions; TYPE_13__* xpathCtxt; TYPE_4__* extras; TYPE_3__* style; scalar_t__ prof; scalar_t__ profMax; scalar_t__ profNr; int /*<<< orphan*/ * profTab; int /*<<< orphan*/  maxTemplateVars; scalar_t__ varsBase; int /*<<< orphan*/ * vars; scalar_t__ varsNr; int /*<<< orphan*/ * varsTab; int /*<<< orphan*/  maxTemplateDepth; int /*<<< orphan*/ * templ; scalar_t__ templNr; int /*<<< orphan*/ * templTab; int /*<<< orphan*/ * dict; int /*<<< orphan*/ * cache; } ;
struct TYPE_18__ {int /*<<< orphan*/  nsHash; } ;

/* Variables and functions */
 scalar_t__ XSLT_DEBUG_NONE ; 
 int /*<<< orphan*/  XSLT_PARSE_OPTIONS ; 
 int /*<<< orphan*/  XSLT_REGISTER_FUNCTION_LOOKUP (TYPE_2__*) ; 
 int /*<<< orphan*/  XSLT_REGISTER_VARIABLE_LOOKUP (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xmlDictCreateSub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 
 int xmlXPathContextSetCache (TYPE_13__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlXPathInit () ; 
 TYPE_13__* xmlXPathNewContext (scalar_t__) ; 
 int /*<<< orphan*/  xmlXPathOrderDocElems (scalar_t__) ; 
 scalar_t__ xslDebugStatus ; 
 int /*<<< orphan*/  xsltDefaultTrace ; 
 int /*<<< orphan*/  xsltFreeTransformContext (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltGetDefaultSecurityPrefs () ; 
 int /*<<< orphan*/  xsltGetXIncludeDefault () ; 
 int /*<<< orphan*/  xsltInitCtxtExts (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltInitGlobals () ; 
 int /*<<< orphan*/  xsltMaxDepth ; 
 int /*<<< orphan*/  xsltMaxVars ; 
 TYPE_5__* xsltNewDocument (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * xsltTransformCacheCreate () ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

xsltTransformContextPtr
xsltNewTransformContext(xsltStylesheetPtr style, xmlDocPtr doc) {
    xsltTransformContextPtr cur;
    xsltDocumentPtr docu;
    int i;

    xsltInitGlobals();

    cur = (xsltTransformContextPtr) xmlMalloc(sizeof(xsltTransformContext));
    if (cur == NULL) {
	xsltTransformError(NULL, NULL, (xmlNodePtr)doc,
		"xsltNewTransformContext : malloc failed\n");
	return(NULL);
    }
    memset(cur, 0, sizeof(xsltTransformContext));

    cur->cache = xsltTransformCacheCreate();
    if (cur->cache == NULL)
	goto internal_err;
    /*
     * setup of the dictionary must be done early as some of the
     * processing later like key handling may need it.
     */
    cur->dict = xmlDictCreateSub(style->dict);
    cur->internalized = ((style->internalized) && (cur->dict != NULL));
#ifdef WITH_XSLT_DEBUG
    xsltGenericDebug(xsltGenericDebugContext,
	     "Creating sub-dictionary from stylesheet for transformation\n");
#endif

    /*
     * initialize the template stack
     */
    cur->templTab = (xsltTemplatePtr *)
	        xmlMalloc(10 * sizeof(xsltTemplatePtr));
    if (cur->templTab == NULL) {
	xsltTransformError(NULL, NULL, (xmlNodePtr) doc,
		"xsltNewTransformContext: out of memory\n");
	goto internal_err;
    }
    cur->templNr = 0;
    cur->templMax = 5;
    cur->templ = NULL;
    cur->maxTemplateDepth = xsltMaxDepth;

    /*
     * initialize the variables stack
     */
    cur->varsTab = (xsltStackElemPtr *)
	        xmlMalloc(10 * sizeof(xsltStackElemPtr));
    if (cur->varsTab == NULL) {
        xmlGenericError(xmlGenericErrorContext,
		"xsltNewTransformContext: out of memory\n");
	goto internal_err;
    }
    cur->varsNr = 0;
    cur->varsMax = 10;
    cur->vars = NULL;
    cur->varsBase = 0;
    cur->maxTemplateVars = xsltMaxVars;

    /*
     * the profiling stack is not initialized by default
     */
    cur->profTab = NULL;
    cur->profNr = 0;
    cur->profMax = 0;
    cur->prof = 0;

    cur->style = style;
    xmlXPathInit();
    cur->xpathCtxt = xmlXPathNewContext(doc);
    if (cur->xpathCtxt == NULL) {
	xsltTransformError(NULL, NULL, (xmlNodePtr) doc,
		"xsltNewTransformContext : xmlXPathNewContext failed\n");
	goto internal_err;
    }
    /*
    * Create an XPath cache.
    */
    if (xmlXPathContextSetCache(cur->xpathCtxt, 1, -1, 0) == -1)
	goto internal_err;
    /*
     * Initialize the extras array
     */
    if (style->extrasNr != 0) {
	cur->extrasMax = style->extrasNr + 20;
	cur->extras = (xsltRuntimeExtraPtr)
	    xmlMalloc(cur->extrasMax * sizeof(xsltRuntimeExtra));
	if (cur->extras == NULL) {
	    xmlGenericError(xmlGenericErrorContext,
		    "xsltNewTransformContext: out of memory\n");
	    goto internal_err;
	}
	cur->extrasNr = style->extrasNr;
	for (i = 0;i < cur->extrasMax;i++) {
	    cur->extras[i].info = NULL;
	    cur->extras[i].deallocate = NULL;
	    cur->extras[i].val.ptr = NULL;
	}
    } else {
	cur->extras = NULL;
	cur->extrasNr = 0;
	cur->extrasMax = 0;
    }

    XSLT_REGISTER_VARIABLE_LOOKUP(cur);
    XSLT_REGISTER_FUNCTION_LOOKUP(cur);
    cur->xpathCtxt->nsHash = style->nsHash;
    /*
     * Initialize the registered external modules
     */
    xsltInitCtxtExts(cur);
    /*
     * Setup document element ordering for later efficiencies
     * (bug 133289)
     */
    if (xslDebugStatus == XSLT_DEBUG_NONE)
        xmlXPathOrderDocElems(doc);
    /*
     * Must set parserOptions before calling xsltNewDocument
     * (bug 164530)
     */
    cur->parserOptions = XSLT_PARSE_OPTIONS;
    docu = xsltNewDocument(cur, doc);
    if (docu == NULL) {
	xsltTransformError(cur, NULL, (xmlNodePtr)doc,
		"xsltNewTransformContext : xsltNewDocument failed\n");
	goto internal_err;
    }
    docu->main = 1;
    cur->document = docu;
    cur->inst = NULL;
    cur->outputFile = NULL;
    cur->sec = xsltGetDefaultSecurityPrefs();
    cur->debugStatus = xslDebugStatus;
    cur->traceCode = (unsigned long*) &xsltDefaultTrace;
    cur->xinclude = xsltGetXIncludeDefault();
    cur->keyInitLevel = 0;

    return(cur);

internal_err:
    if (cur != NULL)
	xsltFreeTransformContext(cur);
    return(NULL);
}