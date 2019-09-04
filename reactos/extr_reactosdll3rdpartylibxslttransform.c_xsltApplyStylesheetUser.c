#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  xsltApplyStylesheetInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

xmlDocPtr
xsltApplyStylesheetUser(xsltStylesheetPtr style, xmlDocPtr doc,
                            const char **params, const char *output,
                            FILE * profile, xsltTransformContextPtr userCtxt)
{
    xmlDocPtr res;

    res = xsltApplyStylesheetInternal(style, doc, params, output,
	                              profile, userCtxt);
    return (res);
}