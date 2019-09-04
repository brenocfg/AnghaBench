#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltExtDataPtr ;
typedef  int /*<<< orphan*/ * xmlHashTablePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_6__ {int /*<<< orphan*/ * extData; } ;
struct TYPE_5__ {int /*<<< orphan*/ * extInfos; } ;

/* Variables and functions */
 TYPE_2__* xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

xmlHashTablePtr
xsltGetExtInfo(xsltStylesheetPtr style, const xmlChar * URI)
{
    xsltExtDataPtr data;

    /*
    * TODO: Why do we have a return type of xmlHashTablePtr?
    *   Is the user-allocated data for extension modules expected
    *   to be a xmlHashTablePtr only? Or is this intended for
    *   the EXSLT module only?
    */

    if (style != NULL && style->extInfos != NULL) {
        data = xmlHashLookup(style->extInfos, URI);
        if (data != NULL && data->extData != NULL)
            return data->extData;
    }
    return NULL;
}