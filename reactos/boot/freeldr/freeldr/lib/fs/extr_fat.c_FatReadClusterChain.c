#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {scalar_t__ SectorsPerCluster; scalar_t__ BytesPerSector; } ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__* PUINT32 ;
typedef  TYPE_1__* PFAT_VOLUME_INFO ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ FatReadAdjacentClusters (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
BOOLEAN FatReadClusterChain(PFAT_VOLUME_INFO Volume, UINT32 StartClusterNumber, UINT32 NumberOfClusters, PVOID Buffer, PUINT32 LastClusterNumber)
{
    UINT32 ClustersRead, NextClusterNumber, ClustersLeft = NumberOfClusters;

    TRACE("FatReadClusterChain() StartClusterNumber = %d NumberOfClusters = %d Buffer = 0x%x\n", StartClusterNumber, NumberOfClusters, Buffer);

    ASSERT(NumberOfClusters > 0);        

    while (FatReadAdjacentClusters(Volume, StartClusterNumber, ClustersLeft, Buffer, &ClustersRead, &NextClusterNumber))
    {
        ClustersLeft -= ClustersRead;
        Buffer = (PVOID)((ULONG_PTR)Buffer + (ClustersRead * Volume->SectorsPerCluster * Volume->BytesPerSector));
        StartClusterNumber = NextClusterNumber;
    }

    if (LastClusterNumber)
    {
        *LastClusterNumber = NextClusterNumber;
    }

    return (ClustersRead > 0);
}