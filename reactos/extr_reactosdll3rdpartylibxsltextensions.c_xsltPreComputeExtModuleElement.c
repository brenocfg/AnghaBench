#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltStylesheetPtr ;
typedef  TYPE_2__* xsltExtElementPtr ;
typedef  int /*<<< orphan*/ * xsltElemPreCompPtr ;
typedef  TYPE_3__* xmlNodePtr ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__* ns; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  transform; int /*<<< orphan*/ * (* precomp ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  href; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlHashLookup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltElementsHash ; 
 int /*<<< orphan*/  xsltExtMutex ; 
 int /*<<< orphan*/ * xsltNewElemPreComp (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

xsltElemPreCompPtr
xsltPreComputeExtModuleElement(xsltStylesheetPtr style, xmlNodePtr inst)
{
    xsltExtElementPtr ext;
    xsltElemPreCompPtr comp = NULL;

    if ((style == NULL) || (inst == NULL) ||
        (inst->type != XML_ELEMENT_NODE) || (inst->ns == NULL))
        return (NULL);

    xmlMutexLock(xsltExtMutex);

    ext = (xsltExtElementPtr)
        xmlHashLookup2(xsltElementsHash, inst->name, inst->ns->href);

    xmlMutexUnlock(xsltExtMutex);

    /*
    * EXT TODO: Now what?
    */
    if (ext == NULL)
        return (NULL);

    if (ext->precomp != NULL) {
	/*
	* REVISIT TODO: Check if the text below is correct.
	* This will return a xsltElemPreComp structure or NULL.
	* 1) If the the author of the extension needs a
	*  custom structure to hold the specific values of
	*  this extension, he will derive a structure based on
	*  xsltElemPreComp; thus we obviously *cannot* refactor
	*  the xsltElemPreComp structure, since all already derived
	*  user-defined strucures will break.
	*  Example: For the extension xsl:document,
	*   in xsltDocumentComp() (preproc.c), the structure
	*   xsltStyleItemDocument is allocated, filled with
	*   specific values and returned.
	* 2) If the author needs no values to be stored in
	*  this structure, then he'll return NULL;
	*/
        comp = ext->precomp(style, inst, ext->transform);
    }
    if (comp == NULL) {
	/*
	* Default creation of a xsltElemPreComp structure, if
	* the author of this extension did not create a custom
	* structure.
	*/
        comp = xsltNewElemPreComp(style, inst, ext->transform);
    }

    return (comp);
}