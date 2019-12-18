#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltExtDataPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {void* extData; } ;
struct TYPE_8__ {int /*<<< orphan*/ * extInfos; struct TYPE_8__* parent; } ;

/* Variables and functions */
 scalar_t__ xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xsltExtensionsHash ; 
 TYPE_1__* xsltNextImport (TYPE_1__*) ; 
 TYPE_2__* xsltStyleInitializeStylesheetModule (TYPE_1__*,int /*<<< orphan*/  const*) ; 

void *
xsltStyleGetExtData(xsltStylesheetPtr style, const xmlChar * URI)
{
    xsltExtDataPtr dataContainer = NULL;
    xsltStylesheetPtr tmpStyle;

    if ((style == NULL) || (URI == NULL) ||
	(xsltExtensionsHash == NULL))
	return (NULL);


#ifdef XSLT_REFACTORED
    /*
    * This is intended for global storage, so only the main
    * stylesheet will hold the data.
    */
    tmpStyle = style;
    while (tmpStyle->parent != NULL)
	tmpStyle = tmpStyle->parent;
    if (tmpStyle->extInfos != NULL) {
	dataContainer =
	    (xsltExtDataPtr) xmlHashLookup(tmpStyle->extInfos, URI);
	if (dataContainer != NULL) {
	    /*
	    * The module was already initialized in the context
	    * of this stylesheet; just return the user-data that
	    * comes with it.
	    */
	    return(dataContainer->extData);
	}
    }
#else
    /*
    * Old behaviour.
    */
    tmpStyle = style;
    while (tmpStyle != NULL) {
	if (tmpStyle->extInfos != NULL) {
	    dataContainer =
		(xsltExtDataPtr) xmlHashLookup(tmpStyle->extInfos, URI);
	    if (dataContainer != NULL) {
		return(dataContainer->extData);
	    }
	}
	tmpStyle = xsltNextImport(tmpStyle);
    }
    tmpStyle = style;
#endif

    dataContainer =
        xsltStyleInitializeStylesheetModule(tmpStyle, URI);
    if (dataContainer != NULL)
	return (dataContainer->extData);
    return(NULL);
}