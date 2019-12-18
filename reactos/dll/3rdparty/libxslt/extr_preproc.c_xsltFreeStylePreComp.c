#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_3__* xsltStylePreCompPtr ;
typedef  TYPE_4__* xsltStyleItemWithParamPtr ;
typedef  TYPE_5__* xsltStyleItemWhenPtr ;
typedef  TYPE_6__* xsltStyleItemVariablePtr ;
typedef  TYPE_7__* xsltStyleItemValueOfPtr ;
typedef  TYPE_8__* xsltStyleItemSortPtr ;
typedef  TYPE_9__* xsltStyleItemParamPtr ;
typedef  TYPE_10__* xsltStyleItemNumberPtr ;
typedef  TYPE_11__* xsltStyleItemIfPtr ;
typedef  TYPE_12__* xsltStyleItemForEachPtr ;
typedef  TYPE_13__* xsltStyleItemCopyOfPtr ;
typedef  TYPE_14__* xsltStyleItemApplyTemplatesPtr ;
typedef  scalar_t__ xsltLocale ;
struct TYPE_30__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_29__ {scalar_t__ locale; int /*<<< orphan*/ * comp; } ;
struct TYPE_28__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_27__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_26__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_25__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_23__ {int /*<<< orphan*/ * fromPat; int /*<<< orphan*/ * countPat; } ;
struct TYPE_24__ {int type; scalar_t__ locale; struct TYPE_24__* nsList; TYPE_2__ numdata; int /*<<< orphan*/ * comp; } ;
struct TYPE_22__ {int /*<<< orphan*/ * fromPat; int /*<<< orphan*/ * countPat; } ;
struct TYPE_21__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_20__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_19__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_18__ {int /*<<< orphan*/ * comp; } ;
struct TYPE_17__ {TYPE_1__ numdata; } ;

/* Variables and functions */
#define  XSLT_FUNC_APPLYIMPORTS 154 
#define  XSLT_FUNC_APPLYTEMPLATES 153 
#define  XSLT_FUNC_ATTRIBUTE 152 
#define  XSLT_FUNC_ATTRSET 151 
#define  XSLT_FUNC_CALLTEMPLATE 150 
#define  XSLT_FUNC_CHOOSE 149 
#define  XSLT_FUNC_COMMENT 148 
#define  XSLT_FUNC_COPY 147 
#define  XSLT_FUNC_COPYOF 146 
#define  XSLT_FUNC_DOCUMENT 145 
#define  XSLT_FUNC_ELEMENT 144 
#define  XSLT_FUNC_FALLBACK 143 
#define  XSLT_FUNC_FOREACH 142 
#define  XSLT_FUNC_IF 141 
#define  XSLT_FUNC_INCLUDE 140 
#define  XSLT_FUNC_LITERAL_RESULT_ELEMENT 139 
#define  XSLT_FUNC_MESSAGE 138 
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
 int /*<<< orphan*/  xmlFree (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeCompMatchList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeLocale (scalar_t__) ; 

__attribute__((used)) static void
xsltFreeStylePreComp(xsltStylePreCompPtr comp) {
    if (comp == NULL)
	return;
#ifdef XSLT_REFACTORED
    /*
    * URGENT TODO: Implement destructors.
    */
    switch (comp->type) {
	case XSLT_FUNC_LITERAL_RESULT_ELEMENT:
	    break;
	case XSLT_FUNC_COPY:
            break;
        case XSLT_FUNC_SORT: {
		xsltStyleItemSortPtr item = (xsltStyleItemSortPtr) comp;
		if (item->locale != (xsltLocale)0)
		    xsltFreeLocale(item->locale);
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
            break;
        case XSLT_FUNC_TEXT:
            break;
        case XSLT_FUNC_ELEMENT:
            break;
        case XSLT_FUNC_ATTRIBUTE:
            break;
        case XSLT_FUNC_COMMENT:
            break;
        case XSLT_FUNC_PI:
	    break;
        case XSLT_FUNC_COPYOF: {
		xsltStyleItemCopyOfPtr item = (xsltStyleItemCopyOfPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
            break;
        case XSLT_FUNC_VALUEOF: {
		xsltStyleItemValueOfPtr item = (xsltStyleItemValueOfPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
            break;
        case XSLT_FUNC_NUMBER: {
                xsltStyleItemNumberPtr item = (xsltStyleItemNumberPtr) comp;
                if (item->numdata.countPat != NULL)
                    xsltFreeCompMatchList(item->numdata.countPat);
                if (item->numdata.fromPat != NULL)
                    xsltFreeCompMatchList(item->numdata.fromPat);
            }
            break;
        case XSLT_FUNC_APPLYIMPORTS:
            break;
        case XSLT_FUNC_CALLTEMPLATE:
            break;
        case XSLT_FUNC_APPLYTEMPLATES: {
		xsltStyleItemApplyTemplatesPtr item =
		    (xsltStyleItemApplyTemplatesPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
            break;
        case XSLT_FUNC_CHOOSE:
            break;
        case XSLT_FUNC_IF: {
		xsltStyleItemIfPtr item = (xsltStyleItemIfPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
            break;
        case XSLT_FUNC_FOREACH: {
		xsltStyleItemForEachPtr item =
		    (xsltStyleItemForEachPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
            break;
        case XSLT_FUNC_DOCUMENT:
            break;
	case XSLT_FUNC_WITHPARAM: {
		xsltStyleItemWithParamPtr item =
		    (xsltStyleItemWithParamPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
	    break;
	case XSLT_FUNC_PARAM: {
		xsltStyleItemParamPtr item =
		    (xsltStyleItemParamPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
	    break;
	case XSLT_FUNC_VARIABLE: {
		xsltStyleItemVariablePtr item =
		    (xsltStyleItemVariablePtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
	    break;
	case XSLT_FUNC_WHEN: {
		xsltStyleItemWhenPtr item =
		    (xsltStyleItemWhenPtr) comp;
		if (item->comp != NULL)
		    xmlXPathFreeCompExpr(item->comp);
	    }
	    break;
	case XSLT_FUNC_OTHERWISE:
	case XSLT_FUNC_FALLBACK:
	case XSLT_FUNC_MESSAGE:
	case XSLT_FUNC_INCLUDE:
	case XSLT_FUNC_ATTRSET:

	    break;
	default:
	    /* TODO: Raise error. */
	    break;
    }
#else
    if (comp->locale != (xsltLocale)0)
	xsltFreeLocale(comp->locale);
    if (comp->comp != NULL)
	xmlXPathFreeCompExpr(comp->comp);
    if (comp->numdata.countPat != NULL)
        xsltFreeCompMatchList(comp->numdata.countPat);
    if (comp->numdata.fromPat != NULL)
        xsltFreeCompMatchList(comp->numdata.fromPat);
    if (comp->nsList != NULL)
	xmlFree(comp->nsList);
#endif

    xmlFree(comp);
}