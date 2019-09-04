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
typedef  int /*<<< orphan*/  xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  xsltApplyStylesheetInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

xmlDocPtr
xsltProfileStylesheet(xsltStylesheetPtr style, xmlDocPtr doc,
                      const char **params, FILE * output)
{
    xmlDocPtr res;

    res = xsltApplyStylesheetInternal(style, doc, params, NULL, output, NULL);
    return (res);
}