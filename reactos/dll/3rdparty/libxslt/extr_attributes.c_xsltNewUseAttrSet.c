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
typedef  TYPE_1__* xsltUseAttrSetPtr ;
typedef  int /*<<< orphan*/  xsltUseAttrSet ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int /*<<< orphan*/  const* ns; int /*<<< orphan*/  const* ncname; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 

__attribute__((used)) static xsltUseAttrSetPtr
xsltNewUseAttrSet(const xmlChar *ncname, const xmlChar *ns) {
    xsltUseAttrSetPtr cur;

    cur = (xsltUseAttrSetPtr) xmlMalloc(sizeof(xsltUseAttrSet));
    if (cur == NULL) {
        xsltGenericError(xsltGenericErrorContext,
		"xsltNewUseAttrSet : malloc failed\n");
	return(NULL);
    }
    memset(cur, 0, sizeof(xsltUseAttrSet));
    cur->ncname = ncname;
    cur->ns = ns;
    return(cur);
}