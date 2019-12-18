#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UCHAR ;
struct TYPE_8__ {size_t HighPart; size_t LowPart; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
struct TYPE_10__ {size_t LowPart; size_t HighPart; } ;
struct TYPE_9__ {int dwLength; size_t dwMemoryLoad; size_t dwTotalPhys; size_t dwTotalPageFile; size_t dwAvailPhys; size_t dwTotalVirtual; size_t dwAvailPageFile; size_t dwAvailVirtual; } ;
typedef  size_t* PDWORD ;
typedef  int /*<<< orphan*/  MemoryStatus ;
typedef  TYPE_2__ MEMORYSTATUS ;
typedef  TYPE_3__ LUID ;
typedef  TYPE_4__ LARGE_INTEGER ;
typedef  size_t DWORD ;
typedef  int CHAR ;

/* Variables and functions */
 int ANSI_NULL ; 
 scalar_t__ AllocateLocallyUniqueId (TYPE_3__*) ; 
 scalar_t__ GetComputerNameA (int*,size_t*) ; 
 scalar_t__ GetDiskFreeSpaceA (char*,size_t*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  GlobalMemoryStatus (TYPE_2__*) ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 scalar_t__ QueryPerformanceCounter (TYPE_4__*) ; 
 int SEED_BUFFER_SIZE ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static VOID
CookupNodeId(UCHAR * NodeId)
{
    CHAR ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
    CHAR * CurrentChar;
    DWORD Size;
    LARGE_INTEGER PerformanceCount;
    PDWORD NodeBegin, NodeMiddle;
    DWORD dwValue;
    MEMORYSTATUS MemoryStatus;
    LUID Luid;
    DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;

    /* Initialize node id */
    memset(NodeId, 0x11, SEED_BUFFER_SIZE * sizeof(UCHAR));

    /* Randomize it with computer name */
    Size = MAX_COMPUTERNAME_LENGTH + 1;
    if (GetComputerNameA(ComputerName, &Size))
    {
        Size = 0;
        CurrentChar = &ComputerName[0];
        while (*CurrentChar != ANSI_NULL)
        {
            NodeId[Size] ^= *CurrentChar;
            ++CurrentChar;

            /* Don't overflow our NodeId */
            if (++Size >= SEED_BUFFER_SIZE)
            {
                Size = 0;
            }
        }
    }

    /* Now, we'll work directly on DWORD values */
    NodeBegin = (DWORD *)&NodeId[0];
    NodeMiddle = (DWORD *)&NodeId[2];

    /* Randomize with performance counter */
    if (QueryPerformanceCounter(&PerformanceCount))
    {
        *NodeMiddle = *NodeMiddle ^ PerformanceCount.u.HighPart ^ PerformanceCount.u.LowPart;

        dwValue = PerformanceCount.u.HighPart ^ PerformanceCount.u.LowPart ^ *NodeBegin;
    }
    else
    {
        dwValue = *NodeBegin;
    }

    *NodeBegin = *NodeBegin ^ dwValue;
    *NodeMiddle = *NodeMiddle ^ *NodeBegin;

    /* Then, with memory status */
    MemoryStatus.dwLength = sizeof(MemoryStatus);
    GlobalMemoryStatus(&MemoryStatus);

    *NodeBegin = *NodeBegin ^ MemoryStatus.dwMemoryLoad;
    *NodeMiddle = *NodeMiddle ^ MemoryStatus.dwTotalPhys;
    *NodeBegin = *NodeBegin ^ MemoryStatus.dwTotalPageFile ^ MemoryStatus.dwAvailPhys;
    *NodeMiddle = *NodeMiddle ^ MemoryStatus.dwTotalVirtual ^ MemoryStatus.dwAvailPageFile;
    *NodeBegin = *NodeBegin ^ MemoryStatus.dwAvailVirtual;

    /* With a LUID */
    if (AllocateLocallyUniqueId(&Luid))
    {
        *NodeBegin = *NodeBegin ^ Luid.LowPart;
        *NodeMiddle = *NodeMiddle ^ Luid.HighPart;
    }

    /* And finally with free disk space */
    if (GetDiskFreeSpaceA("c:\\", &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters))
    {
        *NodeMiddle = *NodeMiddle ^ TotalNumberOfClusters * BytesPerSector * SectorsPerCluster;
        *NodeBegin = *NodeBegin ^ NumberOfFreeClusters * BytesPerSector * SectorsPerCluster;
    }

    /*
     * Because it was locally generated, force the seed to be local
     * setting this, will trigger the check for validness in the kernel
     * and make the seed local
     */
    NodeId[0] |= 0x80u;
}