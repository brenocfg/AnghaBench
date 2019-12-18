#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIDocShell ;
typedef  int /*<<< orphan*/  nsIContentViewer ;
struct TYPE_3__ {scalar_t__ navigation; } ;
typedef  TYPE_1__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  IID_nsIDocShell ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  TRACE (char*,float) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_nsinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIContentViewer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIContentViewer_SetFullZoom (int /*<<< orphan*/ *,float) ; 
 scalar_t__ nsIDocShell_GetContentViewer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDocShell_Release (int /*<<< orphan*/ *) ; 

void set_viewer_zoom(NSContainer *nscontainer, float factor)
{
    nsIContentViewer *content_viewer;
    nsIDocShell *doc_shell;
    nsresult nsres;

    TRACE("Setting to %f\n", factor);

    nsres = get_nsinterface((nsISupports*)nscontainer->navigation, &IID_nsIDocShell, (void**)&doc_shell);
    assert(nsres == NS_OK);

    nsres = nsIDocShell_GetContentViewer(doc_shell, &content_viewer);
    assert(nsres == NS_OK && content_viewer);
    nsIDocShell_Release(doc_shell);

    nsres = nsIContentViewer_SetFullZoom(content_viewer, factor);
    if(NS_FAILED(nsres))
        ERR("SetFullZoom failed: %08x\n", nsres);

    nsIContentViewer_Release(content_viewer);
}