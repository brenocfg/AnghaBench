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
typedef  int /*<<< orphan*/  xsltExtShutdownFunction ;
typedef  int /*<<< orphan*/  xsltExtInitFunction ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int xsltRegisterExtModuleFull (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xsltRegisterExtModule(const xmlChar * URI,
                      xsltExtInitFunction initFunc,
                      xsltExtShutdownFunction shutdownFunc)
{
    return xsltRegisterExtModuleFull(URI, initFunc, shutdownFunc,
                                     NULL, NULL);
}