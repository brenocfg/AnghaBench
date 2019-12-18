#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMEventTarget ;
struct TYPE_9__ {int /*<<< orphan*/  nsIDOMEventListener_iface; } ;
typedef  TYPE_3__ nsEventListener ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  cpp_bool ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {TYPE_2__* window; } ;
struct TYPE_10__ {TYPE_1__ basedoc; } ;
struct TYPE_8__ {int /*<<< orphan*/  nswindow; } ;
typedef  TYPE_4__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMEventTarget ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMEventTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMEventTarget_RemoveEventListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMWindow_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void detach_nslistener(HTMLDocumentNode *doc, const WCHAR *type, nsEventListener *listener, cpp_bool is_capture)
{
    nsIDOMEventTarget *target;
    nsAString type_str;
    nsresult nsres;

    if(!doc->basedoc.window)
        return;

    nsres = nsIDOMWindow_QueryInterface(doc->basedoc.window->nswindow, &IID_nsIDOMEventTarget, (void**)&target);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMEventTarget interface: %08x\n", nsres);
        return;
    }

    nsAString_InitDepend(&type_str, type);
    nsres = nsIDOMEventTarget_RemoveEventListener(target, &type_str,
            &listener->nsIDOMEventListener_iface, is_capture);
    nsAString_Finish(&type_str);
    nsIDOMEventTarget_Release(target);
    if(NS_FAILED(nsres))
        ERR("RemoveEventTarget failed: %08x\n", nsres);
}