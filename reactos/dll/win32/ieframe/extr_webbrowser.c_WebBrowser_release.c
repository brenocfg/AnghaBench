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
struct TYPE_3__ {int /*<<< orphan*/  IWebBrowser2_iface; } ;
typedef  TYPE_1__ WebBrowser ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  IWebBrowser2_Release (int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_DocHost (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ULONG WebBrowser_release(DocHost *iface)
{
    WebBrowser *This = impl_from_DocHost(iface);
    return IWebBrowser2_Release(&This->IWebBrowser2_iface);
}