#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* corhdr; TYPE_2__* nthdr; } ;
struct TYPE_8__ {int MajorRuntimeVersion; scalar_t__ MinorRuntimeVersion; int Flags; } ;
struct TYPE_6__ {scalar_t__ Magic; } ;
struct TYPE_7__ {TYPE_1__ OptionalHeader; } ;
typedef  int /*<<< orphan*/  PEKIND ;
typedef  TYPE_4__ ASSEMBLY ;

/* Variables and functions */
 int COMIMAGE_FLAGS_32BITREQUIRED ; 
 int COMIMAGE_FLAGS_ILONLY ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR64_MAGIC ; 
 int /*<<< orphan*/  peAMD64 ; 
 int /*<<< orphan*/  peI386 ; 
 int /*<<< orphan*/  peMSIL ; 
 int /*<<< orphan*/  peNone ; 

PEKIND assembly_get_architecture(ASSEMBLY *assembly)
{
    if ((assembly->corhdr->MajorRuntimeVersion == 2) && (assembly->corhdr->MinorRuntimeVersion == 0))
        return peNone; /* .NET 1.x assembly */

    if (assembly->nthdr->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
        return peAMD64; /* AMD64/IA64 assembly */

    if ((assembly->corhdr->Flags & COMIMAGE_FLAGS_ILONLY) && !(assembly->corhdr->Flags & COMIMAGE_FLAGS_32BITREQUIRED))
        return peMSIL; /* MSIL assembly */

    return peI386; /* x86 assembly */
}