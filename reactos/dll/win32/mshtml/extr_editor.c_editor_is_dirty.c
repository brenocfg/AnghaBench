#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cpp_bool ;
struct TYPE_7__ {TYPE_2__* doc_obj; } ;
struct TYPE_6__ {TYPE_1__* nscontainer; } ;
struct TYPE_5__ {int /*<<< orphan*/  editor; } ;
typedef  TYPE_3__ HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  nsIEditor_GetDocumentModified (int /*<<< orphan*/ ,scalar_t__*) ; 

HRESULT editor_is_dirty(HTMLDocument *This)
{
    cpp_bool modified;

    if(!This->doc_obj->nscontainer || !This->doc_obj->nscontainer->editor)
        return S_FALSE;

    nsIEditor_GetDocumentModified(This->doc_obj->nscontainer->editor, &modified);

    return modified ? S_OK : S_FALSE;
}