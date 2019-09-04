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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int xsltProcessUserParamInternal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

int
xsltEvalOneUserParam(xsltTransformContextPtr ctxt,
		     const xmlChar * name,
		     const xmlChar * value) {
    return xsltProcessUserParamInternal(ctxt, name, value,
		                        1 /* xpath eval ? */);
}