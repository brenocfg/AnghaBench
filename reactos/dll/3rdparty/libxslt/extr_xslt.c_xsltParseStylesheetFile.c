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
typedef  int /*<<< orphan*/ * xsltSecurityPrefsPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_LOAD_START ; 
 int /*<<< orphan*/  XSLT_PARSE_OPTIONS ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int xsltCheckRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xsltDocDefaultLoader (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltGetDefaultSecurityPrefs () ; 
 int /*<<< orphan*/  xsltInitGlobals () ; 
 int /*<<< orphan*/ * xsltParseStylesheetDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 

xsltStylesheetPtr
xsltParseStylesheetFile(const xmlChar* filename) {
    xsltSecurityPrefsPtr sec;
    xsltStylesheetPtr ret;
    xmlDocPtr doc;

    xsltInitGlobals();

    if (filename == NULL)
	return(NULL);

#ifdef WITH_XSLT_DEBUG_PARSING
    xsltGenericDebug(xsltGenericDebugContext,
	    "xsltParseStylesheetFile : parse %s\n", filename);
#endif

    /*
     * Security framework check
     */
    sec = xsltGetDefaultSecurityPrefs();
    if (sec != NULL) {
	int res;

	res = xsltCheckRead(sec, NULL, filename);
	if (res == 0) {
	    xsltTransformError(NULL, NULL, NULL,
		 "xsltParseStylesheetFile: read rights for %s denied\n",
			     filename);
	    return(NULL);
	}
    }

    doc = xsltDocDefaultLoader(filename, NULL, XSLT_PARSE_OPTIONS,
                               NULL, XSLT_LOAD_START);
    if (doc == NULL) {
	xsltTransformError(NULL, NULL, NULL,
		"xsltParseStylesheetFile : cannot parse %s\n", filename);
	return(NULL);
    }
    ret = xsltParseStylesheetDoc(doc);
    if (ret == NULL) {
	xmlFreeDoc(doc);
	return(NULL);
    }

    return(ret);
}