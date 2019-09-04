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
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;

/* Variables and functions */
 int /*<<< orphan*/  xsltGetNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

xmlNsPtr
xsltGetPlainNamespace(xsltTransformContextPtr ctxt, xmlNodePtr cur,
                      xmlNsPtr ns, xmlNodePtr out)
{
    return(xsltGetNamespace(ctxt, cur, ns, out));
}