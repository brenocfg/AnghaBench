#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltKeyDefPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  char xmlChar ;
struct TYPE_15__ {int /*<<< orphan*/  doc; } ;
struct TYPE_14__ {char const* match; int nsNr; struct TYPE_14__* next; int /*<<< orphan*/ * usecomp; int /*<<< orphan*/ * comp; int /*<<< orphan*/ ** nsList; TYPE_3__* inst; void* use; } ;
struct TYPE_13__ {TYPE_2__* keys; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ IS_BLANK_CH (char const) ; 
 int /*<<< orphan*/  XML_XPATH_NOVAR ; 
 int skipPredicate (char const*,int) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/ ** xmlGetNsList (int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* xmlStrcat (char*,char*) ; 
 void* xmlStrdup (char const*) ; 
 char* xmlStrncat (char*,char const*,int) ; 
 int /*<<< orphan*/  xsltFreeKeyDef (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 TYPE_2__* xsltNewKeyDef (char const*,char const*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,char*,...) ; 
 void* xsltXPathCompile (TYPE_1__*,char const*) ; 
 void* xsltXPathCompileFlags (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

int
xsltAddKey(xsltStylesheetPtr style, const xmlChar *name,
	   const xmlChar *nameURI, const xmlChar *match,
	   const xmlChar *use, xmlNodePtr inst) {
    xsltKeyDefPtr key;
    xmlChar *pattern = NULL;
    int current, end, start, i = 0;

    if ((style == NULL) || (name == NULL) || (match == NULL) || (use == NULL))
	return(-1);

#ifdef WITH_XSLT_DEBUG_KEYS
    xsltGenericDebug(xsltGenericDebugContext,
	"Add key %s, match %s, use %s\n", name, match, use);
#endif

    key = xsltNewKeyDef(name, nameURI);
    key->match = xmlStrdup(match);
    key->use = xmlStrdup(use);
    key->inst = inst;
    key->nsList = xmlGetNsList(inst->doc, inst);
    if (key->nsList != NULL) {
        while (key->nsList[i] != NULL)
	    i++;
    }
    key->nsNr = i;

    /*
     * Split the | and register it as as many keys
     */
    current = end = 0;
    while (match[current] != 0) {
	start = current;
	while (IS_BLANK_CH(match[current]))
	    current++;
	end = current;
	while ((match[end] != 0) && (match[end] != '|')) {
	    if (match[end] == '[') {
	        end = skipPredicate(match, end);
		if (end <= 0) {
		    xsltTransformError(NULL, style, inst,
		        "xsl:key : 'match' pattern is malformed: %s",
		        key->match);
		    if (style != NULL) style->errors++;
		    goto error;
		}
	    } else
		end++;
	}
	if (current == end) {
	    xsltTransformError(NULL, style, inst,
			       "xsl:key : 'match' pattern is empty\n");
	    if (style != NULL) style->errors++;
	    goto error;
	}
	if (match[start] != '/') {
	    pattern = xmlStrcat(pattern, (xmlChar *)"//");
	    if (pattern == NULL) {
		if (style != NULL) style->errors++;
		goto error;
	    }
	}
	pattern = xmlStrncat(pattern, &match[start], end - start);
	if (pattern == NULL) {
	    if (style != NULL) style->errors++;
	    goto error;
	}

	if (match[end] == '|') {
	    pattern = xmlStrcat(pattern, (xmlChar *)"|");
	    end++;
	}
	current = end;
    }
    if (pattern == NULL) {
        xsltTransformError(NULL, style, inst,
                           "xsl:key : 'match' pattern is empty\n");
        if (style != NULL) style->errors++;
        goto error;
    }
#ifdef WITH_XSLT_DEBUG_KEYS
    xsltGenericDebug(xsltGenericDebugContext,
	"   resulting pattern %s\n", pattern);
#endif
    /*
    * XSLT-1: "It is an error for the value of either the use
    *  attribute or the match attribute to contain a
    *  VariableReference."
    * TODO: We should report a variable-reference at compile-time.
    *   Maybe a search for "$", if it occurs outside of quotation
    *   marks, could be sufficient.
    */
#ifdef XML_XPATH_NOVAR
    key->comp = xsltXPathCompileFlags(style, pattern, XML_XPATH_NOVAR);
#else
    key->comp = xsltXPathCompile(style, pattern);
#endif
    if (key->comp == NULL) {
	xsltTransformError(NULL, style, inst,
		"xsl:key : 'match' pattern compilation failed '%s'\n",
		         pattern);
	if (style != NULL) style->errors++;
    }
#ifdef XML_XPATH_NOVAR
    key->usecomp = xsltXPathCompileFlags(style, use, XML_XPATH_NOVAR);
#else
    key->usecomp = xsltXPathCompile(style, use);
#endif
    if (key->usecomp == NULL) {
	xsltTransformError(NULL, style, inst,
		"xsl:key : 'use' expression compilation failed '%s'\n",
		         use);
	if (style != NULL) style->errors++;
    }

    /*
     * Sometimes the stylesheet writer use the order to ease the
     * resolution of keys when they are dependant, keep the provided
     * order so add the new one at the end.
     */
    if (style->keys == NULL) {
	style->keys = key;
    } else {
        xsltKeyDefPtr prev = style->keys;

	while (prev->next != NULL)
	    prev = prev->next;

	prev->next = key;
    }
    key->next = NULL;
    key = NULL;

error:
    if (pattern != NULL)
	xmlFree(pattern);
    if (key != NULL)
        xsltFreeKeyDef(key);
    return(0);
}