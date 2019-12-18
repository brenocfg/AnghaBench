#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  TYPE_2__* xsltStyleItemElementPtr ;
typedef  TYPE_4__* xmlNsPtr ;
typedef  TYPE_5__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_19__ {scalar_t__ type; int /*<<< orphan*/  doc; TYPE_2__* psvi; } ;
struct TYPE_18__ {int /*<<< orphan*/  href; } ;
struct TYPE_17__ {int has_name; int has_ns; int has_use; void* use; int /*<<< orphan*/  const* name; int /*<<< orphan*/  const* nsPrefix; void* ns; TYPE_5__* inst; } ;
struct TYPE_16__ {int /*<<< orphan*/  errors; int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_FUNC_ELEMENT ; 
 void* xmlDictLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlStrncasecmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ xmlValidateQName (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* xsltEvalStaticAttrValueTemplate (TYPE_1__*,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* xsltNewStylePreComp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xsltSplitQName (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_5__*,char*,...) ; 

__attribute__((used)) static void
xsltElementComp(xsltStylesheetPtr style, xmlNodePtr inst) {
#ifdef XSLT_REFACTORED
    xsltStyleItemElementPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif

    /*
    * <xsl:element
    *   name = { qname }
    *   namespace = { uri-reference }
    *   use-attribute-sets = qnames>
    *   <!-- Content: template -->
    * </xsl:element>
    */
    if ((style == NULL) || (inst == NULL) || (inst->type != XML_ELEMENT_NODE))
	return;

#ifdef XSLT_REFACTORED
    comp = (xsltStyleItemElementPtr) xsltNewStylePreComp(style, XSLT_FUNC_ELEMENT);
#else
    comp = xsltNewStylePreComp(style, XSLT_FUNC_ELEMENT);
#endif

    if (comp == NULL)
	return;
    inst->psvi = comp;
    comp->inst = inst;

    /*
    * Attribute "name".
    */
    /*
    * TODO: Precompile the AVT. See bug #344894.
    */
    comp->name = xsltEvalStaticAttrValueTemplate(style, inst,
	(const xmlChar *)"name", NULL, &comp->has_name);
    if (! comp->has_name) {
	xsltTransformError(NULL, style, inst,
	    "xsl:element: The attribute 'name' is missing.\n");
	style->errors++;
	goto error;
    }
    /*
    * Attribute "namespace".
    */
    /*
    * TODO: Precompile the AVT. See bug #344894.
    */
    comp->ns = xsltEvalStaticAttrValueTemplate(style, inst,
	(const xmlChar *)"namespace", NULL, &comp->has_ns);

    if (comp->name != NULL) {
	if (xmlValidateQName(comp->name, 0)) {
	    xsltTransformError(NULL, style, inst,
		"xsl:element: The value '%s' of the attribute 'name' is "
		"not a valid QName.\n", comp->name);
	    style->errors++;
	} else {
	    const xmlChar *prefix = NULL, *name;

	    name = xsltSplitQName(style->dict, comp->name, &prefix);
	    if (comp->has_ns == 0) {
		xmlNsPtr ns;

		/*
		* SPEC XSLT 1.0:
		*  "If the namespace attribute is not present, then the QName is
		*  expanded into an expanded-name using the namespace declarations
		*  in effect for the xsl:element element, including any default
		*  namespace declaration.
		*/
		ns = xmlSearchNs(inst->doc, inst, prefix);
		if (ns != NULL) {
		    comp->ns = xmlDictLookup(style->dict, ns->href, -1);
		    comp->has_ns = 1;
#ifdef XSLT_REFACTORED
		    comp->nsPrefix = prefix;
		    comp->name = name;
#else
                    (void)name; /* Suppress unused variable warning. */
#endif
		} else if (prefix != NULL) {
		    xsltTransformError(NULL, style, inst,
			"xsl:element: The prefixed QName '%s' "
			"has no namespace binding in scope in the "
			"stylesheet; this is an error, since the namespace was "
			"not specified by the instruction itself.\n", comp->name);
		    style->errors++;
		}
	    }
	    if ((prefix != NULL) &&
		(!xmlStrncasecmp(prefix, (xmlChar *)"xml", 3)))
	    {
		/*
		* Mark is to be skipped.
		*/
		comp->has_name = 0;
	    }
	}
    }
    /*
    * Attribute "use-attribute-sets",
    */
    comp->use = xsltEvalStaticAttrValueTemplate(style, inst,
		       (const xmlChar *)"use-attribute-sets",
		       NULL, &comp->has_use);

error:
    return;
}