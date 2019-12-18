#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsAString ;
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  IHTMLWindow2_iface; } ;
struct TYPE_10__ {TYPE_1__ base; struct TYPE_10__* parent; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_2__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IHTMLWindow2_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_frame_by_name (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  get_top_window (TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,char const*) ; 

HTMLOuterWindow *get_target_window(HTMLOuterWindow *window, nsAString *target_str, BOOL *use_new_window)
{
    HTMLOuterWindow *top_window, *ret_window;
    const PRUnichar *target;
    HRESULT hres;

    static const WCHAR _parentW[] = {'_','p','a','r','e','n','t',0};
    static const WCHAR _selfW[] = {'_','s','e','l','f',0};
    static const WCHAR _topW[] = {'_','t','o','p',0};

    *use_new_window = FALSE;

    nsAString_GetData(target_str, &target);
    TRACE("%s\n", debugstr_w(target));

    if(!*target || !strcmpiW(target, _selfW)) {
        IHTMLWindow2_AddRef(&window->base.IHTMLWindow2_iface);
        return window;
    }

    if(!strcmpiW(target, _topW)) {
        get_top_window(window, &top_window);
        IHTMLWindow2_AddRef(&top_window->base.IHTMLWindow2_iface);
        return top_window;
    }

    if(!strcmpiW(target, _parentW)) {
        if(!window->parent) {
            WARN("Window has no parent, treat as self\n");
            IHTMLWindow2_AddRef(&window->base.IHTMLWindow2_iface);
            return window;
        }

        IHTMLWindow2_AddRef(&window->parent->base.IHTMLWindow2_iface);
        return window->parent;
    }

    get_top_window(window, &top_window);

    hres = get_frame_by_name(top_window, target, TRUE, &ret_window);
    if(FAILED(hres) || !ret_window) {
        *use_new_window = TRUE;
        return NULL;
    }

    IHTMLWindow2_AddRef(&ret_window->base.IHTMLWindow2_iface);
    return ret_window;
}