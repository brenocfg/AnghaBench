#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/ * children; } ;
struct TYPE_13__ {TYPE_2__* insert; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_2__*) ; 
 TYPE_2__* xmlNewDocNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNodeGetContent (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltApplyOneTemplate (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

xmlChar *
xsltEvalTemplateString(xsltTransformContextPtr ctxt,
		       xmlNodePtr contextNode,
	               xmlNodePtr inst)
{
    xmlNodePtr oldInsert, insert = NULL;
    xmlChar *ret;

    if ((ctxt == NULL) || (contextNode == NULL) || (inst == NULL) ||
        (inst->type != XML_ELEMENT_NODE))
	return(NULL);

    if (inst->children == NULL)
	return(NULL);

    /*
    * This creates a temporary element-node to add the resulting
    * text content to.
    * OPTIMIZE TODO: Keep such an element-node in the transformation
    *  context to avoid creating it every time.
    */
    insert = xmlNewDocNode(ctxt->output, NULL,
	                   (const xmlChar *)"fake", NULL);
    if (insert == NULL) {
	xsltTransformError(ctxt, NULL, contextNode,
		"Failed to create temporary node\n");
	return(NULL);
    }
    oldInsert = ctxt->insert;
    ctxt->insert = insert;
    /*
    * OPTIMIZE TODO: if inst->children consists only of text-nodes.
    */
    xsltApplyOneTemplate(ctxt, contextNode, inst->children, NULL, NULL);

    ctxt->insert = oldInsert;

    ret = xmlNodeGetContent(insert);
    if (insert != NULL)
	xmlFreeNode(insert);
    return(ret);
}