#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifproxy {int /*<<< orphan*/ * chan; scalar_t__ proxy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRpcChannelBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRpcProxyBuffer_Disconnect (scalar_t__) ; 
 int /*<<< orphan*/  ifproxy_release_public_refs (struct ifproxy*) ; 

__attribute__((used)) static void ifproxy_disconnect(struct ifproxy * This)
{
    ifproxy_release_public_refs(This);
    if (This->proxy) IRpcProxyBuffer_Disconnect(This->proxy);

    IRpcChannelBuffer_Release(This->chan);
    This->chan = NULL;
}