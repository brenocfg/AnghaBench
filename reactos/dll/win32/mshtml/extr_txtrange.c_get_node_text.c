#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ buf; } ;
typedef  TYPE_1__ wstrbuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  nsnode; } ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocString (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstrbuf_append_node_rec (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstrbuf_finish (TYPE_1__*) ; 
 int /*<<< orphan*/  wstrbuf_init (TYPE_1__*) ; 

HRESULT get_node_text(HTMLDOMNode *node, BSTR *ret)
{
    wstrbuf_t buf;
    HRESULT hres = S_OK;

    if (!wstrbuf_init(&buf))
        return E_OUTOFMEMORY;
    wstrbuf_append_node_rec(&buf, node->nsnode);
    if(buf.buf) {
        *ret = SysAllocString(buf.buf);
        if(!*ret)
            hres = E_OUTOFMEMORY;
    } else {
        *ret = NULL;
    }
    wstrbuf_finish(&buf);

    if(SUCCEEDED(hres))
        TRACE("ret %s\n", debugstr_w(*ret));
    return hres;
}