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
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_8__ {TYPE_1__* doc_obj; } ;
struct TYPE_7__ {scalar_t__ nscontainer; } ;
typedef  TYPE_2__ HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  NSCMD_ITALIC ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  UPDATE_UI ; 
 int /*<<< orphan*/  do_ns_command (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_doc (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT exec_italic(HTMLDocument *This, DWORD cmdexecopt, VARIANT *in, VARIANT *out)
{
    TRACE("(%p)\n", This);

    if(in || out)
        FIXME("unsupported args\n");

    if(This->doc_obj->nscontainer)
        do_ns_command(This, NSCMD_ITALIC, NULL);

    update_doc(This, UPDATE_UI);
    return S_OK;
}