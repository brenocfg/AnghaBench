#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_15__ {int /*<<< orphan*/  Ext2CcbLookasideList; } ;
struct TYPE_12__ {scalar_t__ Buffer; scalar_t__ MaximumLength; scalar_t__ Length; } ;
struct TYPE_11__ {int Size; int /*<<< orphan*/  Type; } ;
struct TYPE_14__ {TYPE_2__ DirectorySearchPattern; TYPE_3__* SymLink; int /*<<< orphan*/  Flags; TYPE_1__ Identifier; } ;
struct TYPE_13__ {scalar_t__ Refercount; int /*<<< orphan*/  FullName; } ;
typedef  TYPE_3__* PEXT2_MCB ;
typedef  TYPE_4__* PEXT2_CCB ;
typedef  int /*<<< orphan*/  EXT2_CCB ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DL_INF ; 
 int /*<<< orphan*/  DL_RES ; 
 int /*<<< orphan*/  EXT2CCB ; 
 scalar_t__ ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 TYPE_8__* Ext2Global ; 
 int /*<<< orphan*/  Ext2ReferMcb (TYPE_3__*) ; 
 int /*<<< orphan*/  INC_MEM_COUNT (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  PS_CCB ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,int) ; 

PEXT2_CCB
Ext2AllocateCcb (ULONG Flags, PEXT2_MCB SymLink)
{
    PEXT2_CCB Ccb;

    Ccb = (PEXT2_CCB) (ExAllocateFromNPagedLookasideList(
                           &(Ext2Global->Ext2CcbLookasideList)));
    if (!Ccb) {
        return NULL;
    }

    DEBUG(DL_RES, ( "ExtAllocateCcb: Ccb created: %ph.\n", Ccb));

    RtlZeroMemory(Ccb, sizeof(EXT2_CCB));

    Ccb->Identifier.Type = EXT2CCB;
    Ccb->Identifier.Size = sizeof(EXT2_CCB);
    Ccb->Flags = Flags;

    Ccb->SymLink = SymLink;
    if (SymLink) {
        ASSERT(SymLink->Refercount > 0);
        Ext2ReferMcb(SymLink);
        DEBUG(DL_INF, ( "ExtAllocateCcb: Ccb SymLink: %wZ.\n",
                        &Ccb->SymLink->FullName));
    }

    Ccb->DirectorySearchPattern.Length = 0;
    Ccb->DirectorySearchPattern.MaximumLength = 0;
    Ccb->DirectorySearchPattern.Buffer = 0;

    INC_MEM_COUNT(PS_CCB, Ccb, sizeof(EXT2_CCB));

    return Ccb;
}