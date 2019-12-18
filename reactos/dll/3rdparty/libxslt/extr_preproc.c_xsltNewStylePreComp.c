#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int xsltStyleType ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStylePreComp ;
typedef  int /*<<< orphan*/  xsltStyleItemWithParam ;
typedef  int /*<<< orphan*/  xsltStyleItemWhen ;
typedef  int /*<<< orphan*/  xsltStyleItemVariable ;
typedef  int /*<<< orphan*/  xsltStyleItemValueOf ;
typedef  int /*<<< orphan*/  xsltStyleItemText ;
typedef  int /*<<< orphan*/  xsltStyleItemSort ;
typedef  int /*<<< orphan*/  xsltStyleItemParam ;
typedef  int /*<<< orphan*/  xsltStyleItemPI ;
typedef  int /*<<< orphan*/  xsltStyleItemOtherwise ;
typedef  int /*<<< orphan*/  xsltStyleItemNumber ;
typedef  int /*<<< orphan*/  xsltStyleItemIf ;
typedef  int /*<<< orphan*/  xsltStyleItemForEach ;
typedef  int /*<<< orphan*/  xsltStyleItemElement ;
typedef  int /*<<< orphan*/  xsltStyleItemDocument ;
typedef  int /*<<< orphan*/  xsltStyleItemCopyOf ;
typedef  int /*<<< orphan*/  xsltStyleItemCopy ;
typedef  int /*<<< orphan*/  xsltStyleItemComment ;
typedef  int /*<<< orphan*/  xsltStyleItemChoose ;
typedef  int /*<<< orphan*/  xsltStyleItemCallTemplate ;
typedef  int /*<<< orphan*/  xsltStyleItemAttribute ;
typedef  int /*<<< orphan*/  xsltStyleItemApplyTemplates ;
typedef  int /*<<< orphan*/  xsltStyleItemApplyImports ;
typedef  scalar_t__ xsltElemPreCompPtr ;
struct TYPE_8__ {int type; scalar_t__ next; int /*<<< orphan*/ * func; } ;
struct TYPE_7__ {scalar_t__ preComps; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
#define  XSLT_FUNC_APPLYIMPORTS 149 
#define  XSLT_FUNC_APPLYTEMPLATES 148 
#define  XSLT_FUNC_ATTRIBUTE 147 
#define  XSLT_FUNC_CALLTEMPLATE 146 
#define  XSLT_FUNC_CHOOSE 145 
#define  XSLT_FUNC_COMMENT 144 
#define  XSLT_FUNC_COPY 143 
#define  XSLT_FUNC_COPYOF 142 
#define  XSLT_FUNC_DOCUMENT 141 
#define  XSLT_FUNC_ELEMENT 140 
#define  XSLT_FUNC_FOREACH 139 
#define  XSLT_FUNC_IF 138 
#define  XSLT_FUNC_NUMBER 137 
#define  XSLT_FUNC_OTHERWISE 136 
#define  XSLT_FUNC_PARAM 135 
#define  XSLT_FUNC_PI 134 
#define  XSLT_FUNC_SORT 133 
#define  XSLT_FUNC_TEXT 132 
#define  XSLT_FUNC_VALUEOF 131 
#define  XSLT_FUNC_VARIABLE 130 
#define  XSLT_FUNC_WHEN 129 
#define  XSLT_FUNC_WITHPARAM 128 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/ * xsltApplyImports ; 
 int /*<<< orphan*/ * xsltApplyTemplates ; 
 int /*<<< orphan*/ * xsltAttribute ; 
 int /*<<< orphan*/ * xsltCallTemplate ; 
 int /*<<< orphan*/ * xsltChoose ; 
 int /*<<< orphan*/ * xsltComment ; 
 int /*<<< orphan*/ * xsltCopy ; 
 int /*<<< orphan*/ * xsltCopyOf ; 
 int /*<<< orphan*/ * xsltDocumentElem ; 
 int /*<<< orphan*/ * xsltElement ; 
 int /*<<< orphan*/ * xsltForEach ; 
 int /*<<< orphan*/ * xsltIf ; 
 int /*<<< orphan*/ * xsltNumber ; 
 int /*<<< orphan*/ * xsltProcessingInstruction ; 
 int /*<<< orphan*/ * xsltSort ; 
 int /*<<< orphan*/ * xsltText ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * xsltValueOf ; 

__attribute__((used)) static xsltStylePreCompPtr
xsltNewStylePreComp(xsltStylesheetPtr style, xsltStyleType type) {
    xsltStylePreCompPtr cur;
#ifdef XSLT_REFACTORED
    size_t size;
#endif

    if (style == NULL)
        return(NULL);

#ifdef XSLT_REFACTORED
    /*
    * URGENT TODO: Use specialized factory functions in order
    *   to avoid this ugliness.
    */
    switch (type) {
        case XSLT_FUNC_COPY:
            size = sizeof(xsltStyleItemCopy); break;
        case XSLT_FUNC_SORT:
            size = sizeof(xsltStyleItemSort); break;
        case XSLT_FUNC_TEXT:
            size = sizeof(xsltStyleItemText); break;
        case XSLT_FUNC_ELEMENT:
            size = sizeof(xsltStyleItemElement); break;
        case XSLT_FUNC_ATTRIBUTE:
            size = sizeof(xsltStyleItemAttribute); break;
        case XSLT_FUNC_COMMENT:
            size = sizeof(xsltStyleItemComment); break;
        case XSLT_FUNC_PI:
            size = sizeof(xsltStyleItemPI); break;
        case XSLT_FUNC_COPYOF:
            size = sizeof(xsltStyleItemCopyOf); break;
        case XSLT_FUNC_VALUEOF:
            size = sizeof(xsltStyleItemValueOf); break;;
        case XSLT_FUNC_NUMBER:
            size = sizeof(xsltStyleItemNumber); break;
        case XSLT_FUNC_APPLYIMPORTS:
            size = sizeof(xsltStyleItemApplyImports); break;
        case XSLT_FUNC_CALLTEMPLATE:
            size = sizeof(xsltStyleItemCallTemplate); break;
        case XSLT_FUNC_APPLYTEMPLATES:
            size = sizeof(xsltStyleItemApplyTemplates); break;
        case XSLT_FUNC_CHOOSE:
            size = sizeof(xsltStyleItemChoose); break;
        case XSLT_FUNC_IF:
            size = sizeof(xsltStyleItemIf); break;
        case XSLT_FUNC_FOREACH:
            size = sizeof(xsltStyleItemForEach); break;
        case XSLT_FUNC_DOCUMENT:
            size = sizeof(xsltStyleItemDocument); break;
	case XSLT_FUNC_WITHPARAM:
	    size = sizeof(xsltStyleItemWithParam); break;
	case XSLT_FUNC_PARAM:
	    size = sizeof(xsltStyleItemParam); break;
	case XSLT_FUNC_VARIABLE:
	    size = sizeof(xsltStyleItemVariable); break;
	case XSLT_FUNC_WHEN:
	    size = sizeof(xsltStyleItemWhen); break;
	case XSLT_FUNC_OTHERWISE:
	    size = sizeof(xsltStyleItemOtherwise); break;
	default:
	    xsltTransformError(NULL, style, NULL,
		    "xsltNewStylePreComp : invalid type %d\n", type);
	    style->errors++;
	    return(NULL);
    }
    /*
    * Create the structure.
    */
    cur = (xsltStylePreCompPtr) xmlMalloc(size);
    if (cur == NULL) {
	xsltTransformError(NULL, style, NULL,
		"xsltNewStylePreComp : malloc failed\n");
	style->errors++;
	return(NULL);
    }
    memset(cur, 0, size);

#else /* XSLT_REFACTORED */
    /*
    * Old behaviour.
    */
    cur = (xsltStylePreCompPtr) xmlMalloc(sizeof(xsltStylePreComp));
    if (cur == NULL) {
	xsltTransformError(NULL, style, NULL,
		"xsltNewStylePreComp : malloc failed\n");
	style->errors++;
	return(NULL);
    }
    memset(cur, 0, sizeof(xsltStylePreComp));
#endif /* XSLT_REFACTORED */

    /*
    * URGENT TODO: Better to move this to spezialized factory functions.
    */
    cur->type = type;
    switch (cur->type) {
        case XSLT_FUNC_COPY:
            cur->func = xsltCopy;break;
        case XSLT_FUNC_SORT:
            cur->func = xsltSort;break;
        case XSLT_FUNC_TEXT:
            cur->func = xsltText;break;
        case XSLT_FUNC_ELEMENT:
            cur->func = xsltElement;break;
        case XSLT_FUNC_ATTRIBUTE:
            cur->func = xsltAttribute;break;
        case XSLT_FUNC_COMMENT:
            cur->func = xsltComment;break;
        case XSLT_FUNC_PI:
            cur->func = xsltProcessingInstruction;
	    break;
        case XSLT_FUNC_COPYOF:
            cur->func = xsltCopyOf;break;
        case XSLT_FUNC_VALUEOF:
            cur->func = xsltValueOf;break;
        case XSLT_FUNC_NUMBER:
            cur->func = xsltNumber;break;
        case XSLT_FUNC_APPLYIMPORTS:
            cur->func = xsltApplyImports;break;
        case XSLT_FUNC_CALLTEMPLATE:
            cur->func = xsltCallTemplate;break;
        case XSLT_FUNC_APPLYTEMPLATES:
            cur->func = xsltApplyTemplates;break;
        case XSLT_FUNC_CHOOSE:
            cur->func = xsltChoose;break;
        case XSLT_FUNC_IF:
            cur->func = xsltIf;break;
        case XSLT_FUNC_FOREACH:
            cur->func = xsltForEach;break;
        case XSLT_FUNC_DOCUMENT:
            cur->func = xsltDocumentElem;break;
	case XSLT_FUNC_WITHPARAM:
	case XSLT_FUNC_PARAM:
	case XSLT_FUNC_VARIABLE:
	case XSLT_FUNC_WHEN:
	    break;
	default:
	if (cur->func == NULL) {
	    xsltTransformError(NULL, style, NULL,
		    "xsltNewStylePreComp : no function for type %d\n", type);
	    style->errors++;
	}
    }
    cur->next = style->preComps;
    style->preComps = (xsltElemPreCompPtr) cur;

    return(cur);
}