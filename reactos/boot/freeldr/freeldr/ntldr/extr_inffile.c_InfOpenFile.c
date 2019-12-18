#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_4__ {scalar_t__ HighPart; int LowPart; } ;
struct TYPE_5__ {TYPE_1__ EndingAddress; } ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  PSTR ;
typedef  scalar_t__* PINFCACHE ;
typedef  int /*<<< orphan*/ ** PHINF ;
typedef  scalar_t__ PCSTR ;
typedef  scalar_t__* PCHAR ;
typedef  int /*<<< orphan*/  INFCACHE ;
typedef  int /*<<< orphan*/ * HINF ;
typedef  TYPE_2__ FILEINFORMATION ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ArcClose (int) ; 
 scalar_t__ ArcGetFileInformation (int,TYPE_2__*) ; 
 scalar_t__ ArcOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ArcRead (int,scalar_t__*,int,int*) ; 
 scalar_t__ ESUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpParseBuffer (scalar_t__*,scalar_t__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  OpenReadOnly ; 
 int /*<<< orphan*/  RtlZeroMemory (scalar_t__*,int) ; 
 int /*<<< orphan*/  TAG_INF_CACHE ; 
 int /*<<< orphan*/  TAG_INF_FILE ; 

BOOLEAN
InfOpenFile(
    PHINF InfHandle,
    PCSTR FileName,
    PULONG ErrorLine)
{
    FILEINFORMATION Information;
    ULONG FileId;
    PCHAR FileBuffer;
    ULONG FileSize, Count;
    PINFCACHE Cache;
    BOOLEAN Success;
    ARC_STATUS Status;

    *InfHandle = NULL;
    *ErrorLine = (ULONG) - 1;

    //
    // Open the .inf file
    //
    Status = ArcOpen((PSTR)FileName, OpenReadOnly, &FileId);
    if (Status != ESUCCESS)
    {
        return FALSE;
    }

    //
    // Query file size
    //
    Status = ArcGetFileInformation(FileId, &Information);
    if ((Status != ESUCCESS) || (Information.EndingAddress.HighPart != 0))
    {
        ArcClose(FileId);
        return FALSE;
    }
    FileSize = Information.EndingAddress.LowPart;

    //
    // Allocate buffer to cache the file
    //
    FileBuffer = FrLdrTempAlloc(FileSize + 1, TAG_INF_FILE);
    if (!FileBuffer)
    {
        ArcClose(FileId);
        return FALSE;
    }

    //
    // Read file into memory
    //
    Status = ArcRead(FileId, FileBuffer, FileSize, &Count);
    if ((Status != ESUCCESS) || (Count != FileSize))
    {
        ArcClose(FileId);
        FrLdrTempFree(FileBuffer, TAG_INF_FILE);
        return FALSE;
    }

    //
    // We don't need the file anymore. Close it
    //
    ArcClose(FileId);

    //
    // Append string terminator
    //
    FileBuffer[FileSize] = 0;

    //
    // Allocate infcache header
    //
    Cache = (PINFCACHE)FrLdrTempAlloc(sizeof(INFCACHE), TAG_INF_CACHE);
    if (!Cache)
    {
        FrLdrTempFree(FileBuffer, TAG_INF_FILE);
        return FALSE;
    }

    //
    // Initialize inicache header
    //
    RtlZeroMemory(Cache, sizeof(INFCACHE));

    //
    // Parse the inf buffer
    //
    Success = InfpParseBuffer(Cache,
                              FileBuffer,
                              FileBuffer + FileSize,
                              ErrorLine);
    if (!Success)
    {
        FrLdrTempFree(Cache, TAG_INF_CACHE);
        Cache = NULL;
    }

    //
    // Free file buffer, as it has been parsed
    //
    FrLdrTempFree(FileBuffer, TAG_INF_FILE);

    //
    // Return .inf parsed contents
    //
    *InfHandle = (HINF)Cache;

    return Success;
}