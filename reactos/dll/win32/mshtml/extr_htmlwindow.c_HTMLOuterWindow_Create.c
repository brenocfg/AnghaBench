#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windowref_t ;
typedef  int /*<<< orphan*/  nsIDOMWindow ;
struct TYPE_12__ {int ref; TYPE_2__* window; } ;
struct TYPE_10__ {int /*<<< orphan*/ * inner_window; int /*<<< orphan*/  IHTMLWindow2_iface; TYPE_2__* outer_window; } ;
struct TYPE_11__ {TYPE_1__ base; int /*<<< orphan*/  sibling_entry; int /*<<< orphan*/  children; struct TYPE_11__* parent; int /*<<< orphan*/  entry; int /*<<< orphan*/  task_magic; int /*<<< orphan*/  secmgr; int /*<<< orphan*/  pending_window; int /*<<< orphan*/  readystate; int /*<<< orphan*/  scriptmode; int /*<<< orphan*/ * nswindow; TYPE_4__* window_ref; int /*<<< orphan*/ * doc_obj; } ;
typedef  TYPE_2__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoInternetCreateSecurityManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IHTMLWindow2_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  READYSTATE_UNINITIALIZED ; 
 int /*<<< orphan*/  SCRIPTMODE_GECKO ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* alloc_window (int) ; 
 int /*<<< orphan*/  create_pending_window (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_task_target_magic () ; 
 TYPE_4__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMWindow_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_window_doc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_list ; 

HRESULT HTMLOuterWindow_Create(HTMLDocumentObj *doc_obj, nsIDOMWindow *nswindow,
        HTMLOuterWindow *parent, HTMLOuterWindow **ret)
{
    HTMLOuterWindow *window;
    HRESULT hres;

    window = alloc_window(sizeof(HTMLOuterWindow));
    if(!window)
        return E_OUTOFMEMORY;

    window->base.outer_window = window;
    window->base.inner_window = NULL;

    window->window_ref = heap_alloc(sizeof(windowref_t));
    if(!window->window_ref) {
        heap_free(window);
        return E_OUTOFMEMORY;
    }

    window->doc_obj = doc_obj;

    window->window_ref->window = window;
    window->window_ref->ref = 1;

    if(nswindow) {
        nsIDOMWindow_AddRef(nswindow);
        window->nswindow = nswindow;
    }

    window->scriptmode = parent ? parent->scriptmode : SCRIPTMODE_GECKO;
    window->readystate = READYSTATE_UNINITIALIZED;

    hres = create_pending_window(window, NULL);
    if(SUCCEEDED(hres))
        hres = update_window_doc(window->pending_window);
    if(FAILED(hres)) {
        IHTMLWindow2_Release(&window->base.IHTMLWindow2_iface);
        return hres;
    }

    hres = CoInternetCreateSecurityManager(NULL, &window->secmgr, 0);
    if(FAILED(hres)) {
        IHTMLWindow2_Release(&window->base.IHTMLWindow2_iface);
        return hres;
    }

    window->task_magic = get_task_target_magic();

    list_init(&window->children);
    list_add_head(&window_list, &window->entry);

    if(parent) {
        IHTMLWindow2_AddRef(&window->base.IHTMLWindow2_iface);

        window->parent = parent;
        list_add_tail(&parent->children, &window->sibling_entry);
    }

    TRACE("%p inner_window %p\n", window, window->base.inner_window);

    *ret = window;
    return S_OK;
}