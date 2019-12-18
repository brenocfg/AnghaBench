#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltNsAliasPtr ;
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlHashTablePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_20__ {int hasNsAliases; } ;
struct TYPE_19__ {int /*<<< orphan*/  doc; } ;
struct TYPE_18__ {int /*<<< orphan*/ * href; } ;
struct TYPE_17__ {TYPE_3__* targetNs; TYPE_3__* literalNs; } ;
struct TYPE_16__ {int /*<<< orphan*/ * nsAliases; int /*<<< orphan*/ * defaultAlias; } ;

/* Variables and functions */
 int /*<<< orphan*/ * UNDEFINED_DEFAULT_NS ; 
 TYPE_8__* XSLT_CCTXT (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlGetNsProp (TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashAddEntry (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/ * xmlHashCreate (int) ; 
 TYPE_3__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_2__* xsltNewNsAlias (TYPE_8__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_4__*,char*,...) ; 

void
xsltNamespaceAlias(xsltStylesheetPtr style, xmlNodePtr node)
{
    xmlChar *resultPrefix = NULL;
    xmlChar *stylePrefix = NULL;
    xmlNsPtr literalNs = NULL;
    xmlNsPtr targetNs = NULL;

#ifdef XSLT_REFACTORED
    xsltNsAliasPtr alias;

    if ((style == NULL) || (node == NULL))
	return;

    /*
    * SPEC XSLT 1.0:
    *  "If a namespace URI is declared to be an alias for multiple
    *  different namespace URIs, then the declaration with the highest
    *  import precedence is used. It is an error if there is more than
    *  one such declaration. An XSLT processor may signal the error;
    *  if it does not signal the error, it must recover by choosing,
    *  from amongst the declarations with the highest import precedence,
    *  the one that occurs last in the stylesheet."
    *
    * SPEC TODO: Check for the errors mentioned above.
    */
    /*
    * NOTE that the XSLT 2.0 also *does* use the NULL namespace if
    *  "#default" is used and there's no default namespace is scope.
    *  I.e., this is *not* an error.
    *  Most XSLT 1.0 implementations work this way.
    *  The XSLT 1.0 spec has nothing to say on the subject.
    */
    /*
    * Attribute "stylesheet-prefix".
    */
    stylePrefix = xmlGetNsProp(node, (const xmlChar *)"stylesheet-prefix", NULL);
    if (stylePrefix == NULL) {
	xsltTransformError(NULL, style, node,
	    "The attribute 'stylesheet-prefix' is missing.\n");
	return;
    }
    if (xmlStrEqual(stylePrefix, (const xmlChar *)"#default"))
	literalNs = xmlSearchNs(node->doc, node, NULL);
    else {
	literalNs = xmlSearchNs(node->doc, node, stylePrefix);
	if (literalNs == NULL) {
	    xsltTransformError(NULL, style, node,
	        "Attribute 'stylesheet-prefix': There's no namespace "
		"declaration in scope for the prefix '%s'.\n",
		    stylePrefix);
	    goto error;
	}
    }
    /*
    * Attribute "result-prefix".
    */
    resultPrefix = xmlGetNsProp(node, (const xmlChar *)"result-prefix", NULL);
    if (resultPrefix == NULL) {
	xsltTransformError(NULL, style, node,
	    "The attribute 'result-prefix' is missing.\n");
	goto error;
    }
    if (xmlStrEqual(resultPrefix, (const xmlChar *)"#default"))
	targetNs = xmlSearchNs(node->doc, node, NULL);
    else {
	targetNs = xmlSearchNs(node->doc, node, resultPrefix);

        if (targetNs == NULL) {
	   xsltTransformError(NULL, style, node,
	        "Attribute 'result-prefix': There's no namespace "
		"declaration in scope for the prefix '%s'.\n",
		    stylePrefix);
	    goto error;
	}
    }
    /*
     *
     * Same alias for multiple different target namespace URIs:
     *  TODO: The one with the highest import precedence is used.
     *  Example:
     *  <xsl:namespace-alias stylesheet-prefix="foo"
     *                       result-prefix="bar"/>
     *
     *  <xsl:namespace-alias stylesheet-prefix="foo"
     *                       result-prefix="zar"/>
     *
     * Same target namespace URI for multiple different aliases:
     *  All alias-definitions will be used.
     *  Example:
     *  <xsl:namespace-alias stylesheet-prefix="bar"
     *                       result-prefix="foo"/>
     *
     *  <xsl:namespace-alias stylesheet-prefix="zar"
     *                       result-prefix="foo"/>
     * Cases using #default:
     *  <xsl:namespace-alias stylesheet-prefix="#default"
     *                       result-prefix="#default"/>
     *  TODO: Has this an effect at all?
     *
     *  <xsl:namespace-alias stylesheet-prefix="foo"
     *                       result-prefix="#default"/>
     *  From namespace to no namespace.
     *
     *  <xsl:namespace-alias stylesheet-prefix="#default"
     *                       result-prefix="foo"/>
     *  From no namespace to namespace.
     */


     /*
     * Store the ns-node in the alias-object.
    */
    alias = xsltNewNsAlias(XSLT_CCTXT(style));
    if (alias == NULL)
	return;
    alias->literalNs = literalNs;
    alias->targetNs = targetNs;
    XSLT_CCTXT(style)->hasNsAliases = 1;


#else /* XSLT_REFACTORED */
    const xmlChar *literalNsName;
    const xmlChar *targetNsName;


    if ((style == NULL) || (node == NULL))
	return;

    stylePrefix = xmlGetNsProp(node, (const xmlChar *)"stylesheet-prefix", NULL);
    if (stylePrefix == NULL) {
	xsltTransformError(NULL, style, node,
	    "namespace-alias: stylesheet-prefix attribute missing\n");
	return;
    }
    resultPrefix = xmlGetNsProp(node, (const xmlChar *)"result-prefix", NULL);
    if (resultPrefix == NULL) {
	xsltTransformError(NULL, style, node,
	    "namespace-alias: result-prefix attribute missing\n");
	goto error;
    }

    if (xmlStrEqual(stylePrefix, (const xmlChar *)"#default")) {
	literalNs = xmlSearchNs(node->doc, node, NULL);
	if (literalNs == NULL) {
	    literalNsName = NULL;
	} else
	    literalNsName = literalNs->href; /* Yes - set for nsAlias table */
    } else {
	literalNs = xmlSearchNs(node->doc, node, stylePrefix);

	if ((literalNs == NULL) || (literalNs->href == NULL)) {
	    xsltTransformError(NULL, style, node,
	        "namespace-alias: prefix %s not bound to any namespace\n",
					stylePrefix);
	    goto error;
	} else
	    literalNsName = literalNs->href;
    }

    /*
     * When "#default" is used for result, if a default namespace has not
     * been explicitly declared the special value UNDEFINED_DEFAULT_NS is
     * put into the nsAliases table
     */
    if (xmlStrEqual(resultPrefix, (const xmlChar *)"#default")) {
	targetNs = xmlSearchNs(node->doc, node, NULL);
	if (targetNs == NULL) {
	    targetNsName = UNDEFINED_DEFAULT_NS;
	} else
	    targetNsName = targetNs->href;
    } else {
	targetNs = xmlSearchNs(node->doc, node, resultPrefix);

        if ((targetNs == NULL) || (targetNs->href == NULL)) {
	    xsltTransformError(NULL, style, node,
	        "namespace-alias: prefix %s not bound to any namespace\n",
					resultPrefix);
	    goto error;
	} else
	    targetNsName = targetNs->href;
    }
    /*
     * Special case: if #default is used for
     *  the stylesheet-prefix (literal namespace) and there's no default
     *  namespace in scope, we'll use style->defaultAlias for this.
     */
    if (literalNsName == NULL) {
        if (targetNs != NULL) {
	    /*
	    * BUG TODO: Is it not sufficient to have only 1 field for
	    *  this, since subsequently alias declarations will
	    *  overwrite this.
	    *  Example:
	    *   <xsl:namespace-alias result-prefix="foo"
	    *                        stylesheet-prefix="#default"/>
	    *   <xsl:namespace-alias result-prefix="bar"
	    *                        stylesheet-prefix="#default"/>
	    *  The mapping for "foo" won't be visible anymore.
	    */
            style->defaultAlias = targetNs->href;
	}
    } else {
        if (style->nsAliases == NULL)
	    style->nsAliases = xmlHashCreate(10);
        if (style->nsAliases == NULL) {
	    xsltTransformError(NULL, style, node,
	        "namespace-alias: cannot create hash table\n");
	    goto error;
        }
	xmlHashAddEntry((xmlHashTablePtr) style->nsAliases,
	    literalNsName, (void *) targetNsName);
    }
#endif /* else of XSLT_REFACTORED */

error:
    if (stylePrefix != NULL)
	xmlFree(stylePrefix);
    if (resultPrefix != NULL)
	xmlFree(resultPrefix);
}