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
struct TYPE_8__ {TYPE_2__* nsstream; scalar_t__ nscontext; scalar_t__ nslistener; TYPE_1__* nschannel; } ;
typedef  TYPE_3__ nsChannelBSC ;
struct TYPE_7__ {int /*<<< orphan*/  nsIInputStream_iface; } ;
struct TYPE_6__ {int /*<<< orphan*/  nsIHttpChannel_iface; } ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 TYPE_3__* nsChannelBSC_from_BSCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIHttpChannel_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIInputStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIStreamListener_Release (scalar_t__) ; 
 int /*<<< orphan*/  nsISupports_Release (scalar_t__) ; 

__attribute__((used)) static void nsChannelBSC_destroy(BSCallback *bsc)
{
    nsChannelBSC *This = nsChannelBSC_from_BSCallback(bsc);

    if(This->nschannel)
        nsIHttpChannel_Release(&This->nschannel->nsIHttpChannel_iface);
    if(This->nslistener)
        nsIStreamListener_Release(This->nslistener);
    if(This->nscontext)
        nsISupports_Release(This->nscontext);
    if(This->nsstream)
        nsIInputStream_Release(&This->nsstream->nsIInputStream_iface);
    heap_free(This);
}