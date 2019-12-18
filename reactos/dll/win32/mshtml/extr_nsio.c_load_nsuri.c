#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
struct TYPE_10__ {int /*<<< orphan*/ * channel_bsc; int /*<<< orphan*/  nsIFileURL_iface; } ;
typedef  TYPE_3__ nsWineURI ;
typedef  int /*<<< orphan*/  nsIWebNavigation ;
typedef  int /*<<< orphan*/  nsIURI ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIInputStream ;
typedef  int /*<<< orphan*/  nsIDocShellLoadInfo ;
typedef  int /*<<< orphan*/  nsIDocShell ;
typedef  int /*<<< orphan*/  nsChannelBSC ;
struct TYPE_12__ {int /*<<< orphan*/  skip_mutation_notif; } ;
struct TYPE_9__ {TYPE_1__* inner_window; } ;
struct TYPE_11__ {TYPE_2__ base; scalar_t__ nswindow; } ;
struct TYPE_8__ {TYPE_5__* doc; } ;
typedef  TYPE_4__ HTMLOuterWindow ;
typedef  TYPE_5__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIDocShell ; 
 int /*<<< orphan*/  IID_nsIWebNavigation ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_nsinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDocShellLoadInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDocShellLoadInfo_SetPostDataStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDocShell_CreateLoadInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nsIDocShell_LoadURI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDocShell_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIWebNavigation_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIWebNavigation_Release (int /*<<< orphan*/ *) ; 

HRESULT load_nsuri(HTMLOuterWindow *window, nsWineURI *uri, nsIInputStream *post_stream,
        nsChannelBSC *channelbsc, DWORD flags)
{
    nsIDocShellLoadInfo *load_info = NULL;
    nsIWebNavigation *web_navigation;
    nsIDocShell *doc_shell;
    HTMLDocumentNode *doc;
    nsresult nsres;

    nsres = get_nsinterface((nsISupports*)window->nswindow, &IID_nsIWebNavigation, (void**)&web_navigation);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIWebNavigation interface: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIWebNavigation_QueryInterface(web_navigation, &IID_nsIDocShell, (void**)&doc_shell);
    nsIWebNavigation_Release(web_navigation);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDocShell: %08x\n", nsres);
        return E_FAIL;
    }

    if(post_stream) {
        nsres = nsIDocShell_CreateLoadInfo(doc_shell, &load_info);
        if(NS_FAILED(nsres)) {
            nsIDocShell_Release(doc_shell);
            return E_FAIL;
        }

        nsres = nsIDocShellLoadInfo_SetPostDataStream(load_info, post_stream);
        assert(nsres == NS_OK);
    }

    uri->channel_bsc = channelbsc;
    doc = window->base.inner_window->doc;
    doc->skip_mutation_notif = TRUE;
    nsres = nsIDocShell_LoadURI(doc_shell, (nsIURI*)&uri->nsIFileURL_iface, load_info, flags, FALSE);
    if(doc == window->base.inner_window->doc)
        doc->skip_mutation_notif = FALSE;
    uri->channel_bsc = NULL;
    nsIDocShell_Release(doc_shell);
    if(load_info)
        nsIDocShellLoadInfo_Release(load_info);
    if(NS_FAILED(nsres)) {
        WARN("LoadURI failed: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}