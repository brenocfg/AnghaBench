#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltExtDefPtr ;
typedef  int /*<<< orphan*/  xsltExtDef ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {void* URI; void* prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 void* xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xsltExtDefPtr
xsltNewExtDef(const xmlChar * prefix, const xmlChar * URI)
{
    xsltExtDefPtr cur;

    cur = (xsltExtDefPtr) xmlMalloc(sizeof(xsltExtDef));
    if (cur == NULL) {
        xsltTransformError(NULL, NULL, NULL,
                           "xsltNewExtDef : malloc failed\n");
        return (NULL);
    }
    memset(cur, 0, sizeof(xsltExtDef));
    if (prefix != NULL)
        cur->prefix = xmlStrdup(prefix);
    if (URI != NULL)
        cur->URI = xmlStrdup(URI);
    return (cur);
}