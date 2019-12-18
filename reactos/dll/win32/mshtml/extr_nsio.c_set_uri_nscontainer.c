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
struct TYPE_7__ {TYPE_2__* container; } ;
typedef  TYPE_1__ nsWineURI ;
struct TYPE_8__ {int /*<<< orphan*/  nsIWebBrowserChrome_iface; } ;
typedef  TYPE_2__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nsIWebBrowserChrome_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowserChrome_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_uri_nscontainer(nsWineURI *This, NSContainer *nscontainer)
{
    if(This->container) {
        if(This->container == nscontainer)
            return;
        TRACE("Changing %p -> %p\n", This->container, nscontainer);
        nsIWebBrowserChrome_Release(&This->container->nsIWebBrowserChrome_iface);
    }

    if(nscontainer)
        nsIWebBrowserChrome_AddRef(&nscontainer->nsIWebBrowserChrome_iface);
    This->container = nscontainer;
}