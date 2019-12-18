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
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_10__ {TYPE_1__* uri; } ;
typedef  TYPE_2__ nsChannel ;
struct TYPE_12__ {int /*<<< orphan*/  basedoc; int /*<<< orphan*/  client; } ;
struct TYPE_11__ {TYPE_4__* doc; } ;
struct TYPE_9__ {int /*<<< orphan*/  uri; } ;
typedef  TYPE_3__ NSContainer ;
typedef  TYPE_4__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IUri_GetDisplayUri (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NS_ERROR_FAILURE ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  exec_shldocvw_67 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlink_frame_navigate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static nsresult before_async_open(nsChannel *channel, NSContainer *container, BOOL *cancel)
{
    HTMLDocumentObj *doc = container->doc;
    BSTR display_uri;
    HRESULT hres;

    if(!doc->client) {
        *cancel = TRUE;
        return NS_OK;
    }

    hres = IUri_GetDisplayUri(channel->uri->uri, &display_uri);
    if(FAILED(hres))
        return NS_ERROR_FAILURE;

    if(!exec_shldocvw_67(doc, display_uri)) {
        SysFreeString(display_uri);
        *cancel = FALSE;
        return NS_OK;
    }

    hres = hlink_frame_navigate(&doc->basedoc, display_uri, channel, 0, cancel);
    SysFreeString(display_uri);
    if(FAILED(hres))
        *cancel = TRUE;
    return NS_OK;
}