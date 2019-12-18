#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* Bytes; } ;
struct TYPE_5__ {int ExtensionBlockCount; TYPE_2__* ExtensionBlocks; } ;
typedef  TYPE_1__ Extensions ;
typedef  TYPE_2__ ExtensionBlock ;

/* Variables and functions */
 int /*<<< orphan*/  ungif_free (TYPE_2__*) ; 

__attribute__((used)) static void
FreeExtension(Extensions *Extensions)
{
    ExtensionBlock *ep;

    if ((Extensions == NULL) || (Extensions->ExtensionBlocks == NULL)) {
        return;
    }
    for (ep = Extensions->ExtensionBlocks;
         ep < (Extensions->ExtensionBlocks + Extensions->ExtensionBlockCount); ep++)
        ungif_free(ep->Bytes);
    ungif_free(Extensions->ExtensionBlocks);
    Extensions->ExtensionBlocks = NULL;
}