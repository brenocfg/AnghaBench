#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltStyleExtShutdownFunction ;
typedef  int /*<<< orphan*/  xsltStyleExtInitFunction ;
typedef  int /*<<< orphan*/  xsltExtShutdownFunction ;
typedef  TYPE_1__* xsltExtModulePtr ;
typedef  int /*<<< orphan*/  xsltExtModule ;
typedef  int /*<<< orphan*/  xsltExtInitFunction ;
struct TYPE_3__ {int /*<<< orphan*/  styleShutdownFunc; int /*<<< orphan*/  styleInitFunc; int /*<<< orphan*/  shutdownFunc; int /*<<< orphan*/  initFunc; } ;

/* Variables and functions */
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xsltExtModulePtr
xsltNewExtModule(xsltExtInitFunction initFunc,
                 xsltExtShutdownFunction shutdownFunc,
                 xsltStyleExtInitFunction styleInitFunc,
                 xsltStyleExtShutdownFunction styleShutdownFunc)
{
    xsltExtModulePtr cur;

    cur = (xsltExtModulePtr) xmlMalloc(sizeof(xsltExtModule));
    if (cur == NULL) {
        xsltTransformError(NULL, NULL, NULL,
                           "xsltNewExtModule : malloc failed\n");
        return (NULL);
    }
    cur->initFunc = initFunc;
    cur->shutdownFunc = shutdownFunc;
    cur->styleInitFunc = styleInitFunc;
    cur->styleShutdownFunc = styleShutdownFunc;
    return (cur);
}