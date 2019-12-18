#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/ * children; } ;
struct TYPE_12__ {int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlGetNsProp (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltAddKey (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/ * xsltGetQNameURI (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xsltParseContentError (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,char*) ; 

__attribute__((used)) static void
xsltParseStylesheetKey(xsltStylesheetPtr style, xmlNodePtr key) {
    xmlChar *prop = NULL;
    xmlChar *use = NULL;
    xmlChar *match = NULL;
    xmlChar *name = NULL;
    xmlChar *nameURI = NULL;

    if ((style == NULL) || (key == NULL) || (key->type != XML_ELEMENT_NODE))
	return;

    /*
     * Get arguments
     */
    prop = xmlGetNsProp(key, (const xmlChar *)"name", NULL);
    if (prop != NULL) {
        const xmlChar *URI;

	/*
	* TODO: Don't use xsltGetQNameURI().
	*/
	URI = xsltGetQNameURI(key, &prop);
	if (prop == NULL) {
	    if (style != NULL) style->errors++;
	    goto error;
	} else {
	    name = prop;
	    if (URI != NULL)
		nameURI = xmlStrdup(URI);
	}
#ifdef WITH_XSLT_DEBUG_PARSING
	xsltGenericDebug(xsltGenericDebugContext,
	     "xsltParseStylesheetKey: name %s\n", name);
#endif
    } else {
	xsltTransformError(NULL, style, key,
	    "xsl:key : error missing name\n");
	if (style != NULL) style->errors++;
	goto error;
    }

    match = xmlGetNsProp(key, (const xmlChar *)"match", NULL);
    if (match == NULL) {
	xsltTransformError(NULL, style, key,
	    "xsl:key : error missing match\n");
	if (style != NULL) style->errors++;
	goto error;
    }

    use = xmlGetNsProp(key, (const xmlChar *)"use", NULL);
    if (use == NULL) {
	xsltTransformError(NULL, style, key,
	    "xsl:key : error missing use\n");
	if (style != NULL) style->errors++;
	goto error;
    }

    /*
     * register the keys
     */
    xsltAddKey(style, name, nameURI, match, use, key);


error:
    if (use != NULL)
	xmlFree(use);
    if (match != NULL)
	xmlFree(match);
    if (name != NULL)
	xmlFree(name);
    if (nameURI != NULL)
	xmlFree(nameURI);

    if (key->children != NULL) {
	xsltParseContentError(style, key->children);
    }
}