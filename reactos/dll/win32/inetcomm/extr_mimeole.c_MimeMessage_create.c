#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ body_t ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; int next_index; TYPE_1__ IMimeMessage_iface; int /*<<< orphan*/  body_tree; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_3__ MimeMessage ;
typedef  int /*<<< orphan*/  MimeBody ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MimeMessageVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mimebody_create () ; 
 TYPE_2__* new_body_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT MimeMessage_create(IUnknown *outer, void **obj)
{
    MimeMessage *This;
    MimeBody *mime_body;
    body_t *root_body;

    TRACE("(%p, %p)\n", outer, obj);

    if (outer)
    {
        FIXME("outer unknown not supported yet\n");
        return E_NOTIMPL;
    }

    *obj = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IMimeMessage_iface.lpVtbl = &MimeMessageVtbl;
    This->ref = 1;
    This->stream = NULL;
    list_init(&This->body_tree);
    This->next_index = 1;

    mime_body = mimebody_create();
    root_body = new_body_entry(mime_body, This->next_index++, NULL);
    list_add_head(&This->body_tree, &root_body->entry);

    *obj = &This->IMimeMessage_iface;
    return S_OK;
}