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
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  int* PVOID ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDEReadBlock (int,int*,int) ; 
 int IDEReadStatus (int) ; 
 int /*<<< orphan*/  IDEWriteCommand (int,int) ; 
 int /*<<< orphan*/  IDEWriteCylinderHigh (int,int) ; 
 int /*<<< orphan*/  IDEWriteCylinderLow (int,int) ; 
 int /*<<< orphan*/  IDEWriteDriveControl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDEWriteDriveHead (int,int) ; 
 int /*<<< orphan*/  IDEWritePrecomp (int,int) ; 
 int /*<<< orphan*/  IDEWriteSectorCount (int,int) ; 
 int /*<<< orphan*/  IDEWriteSectorNum (int,int) ; 
 int /*<<< orphan*/  IDE_DC_nIEN ; 
 int IDE_DH_DRV1 ; 
 int IDE_DH_FIXED ; 
 int IDE_DH_LBA ; 
 int IDE_MAX_BUSY_RETRIES ; 
 int IDE_MAX_POLL_RETRIES ; 
 int IDE_SECTOR_BUF_SZ ; 
 int IDE_SR_BUSY ; 
 int IDE_SR_DRQ ; 
 int IDE_SR_ERR ; 
 int /*<<< orphan*/  StallExecutionProcessor (int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static BOOLEAN
XboxDiskPolledRead(ULONG CommandPort,
                   ULONG ControlPort,
                   UCHAR PreComp,
                   UCHAR SectorCnt,
                   UCHAR SectorNum,
                   UCHAR CylinderLow,
                   UCHAR CylinderHigh,
                   UCHAR DrvHead,
                   UCHAR Command,
                   PVOID Buffer)
{
    ULONG SectorCount = 0;
    ULONG RetryCount;
    BOOLEAN Junk = FALSE;
    UCHAR Status;

    /* Wait for BUSY to clear */
    for (RetryCount = 0; RetryCount < IDE_MAX_BUSY_RETRIES; RetryCount++)
    {
        Status = IDEReadStatus(CommandPort);
        if (!(Status & IDE_SR_BUSY))
            break;

        StallExecutionProcessor(10);
    }
    TRACE("status=0x%x\n", Status);
    TRACE("waited %d usecs for busy to clear\n", RetryCount * 10);
    if (RetryCount >= IDE_MAX_BUSY_RETRIES)
    {
        WARN("Drive is BUSY for too long\n");
        return FALSE;
    }

    /* Write Drive/Head to select drive */
    IDEWriteDriveHead(CommandPort, IDE_DH_FIXED | DrvHead);
    StallExecutionProcessor(500);

    /* Disable interrupts */
    IDEWriteDriveControl(ControlPort, IDE_DC_nIEN);
    StallExecutionProcessor(500);

    /* Issue command to drive */
    if (DrvHead & IDE_DH_LBA)
    {
        TRACE("READ:DRV=%d:LBA=1:BLK=%d:SC=0x%x:CM=0x%x\n",
              DrvHead & IDE_DH_DRV1 ? 1 : 0,
              ((DrvHead & 0x0f) << 24) + (CylinderHigh << 16) + (CylinderLow << 8) + SectorNum,
              SectorCnt,
              Command);
    }
    else
    {
        TRACE("READ:DRV=%d:LBA=0:CH=0x%x:CL=0x%x:HD=0x%x:SN=0x%x:SC=0x%x:CM=0x%x\n",
              DrvHead & IDE_DH_DRV1 ? 1 : 0,
              CylinderHigh,
              CylinderLow,
              DrvHead & 0x0f,
              SectorNum,
              SectorCnt,
              Command);
    }

    /* Setup command parameters */
    IDEWritePrecomp(CommandPort, PreComp);
    IDEWriteSectorCount(CommandPort, SectorCnt);
    IDEWriteSectorNum(CommandPort, SectorNum);
    IDEWriteCylinderHigh(CommandPort, CylinderHigh);
    IDEWriteCylinderLow(CommandPort, CylinderLow);
    IDEWriteDriveHead(CommandPort, IDE_DH_FIXED | DrvHead);

    /* Issue the command */
    IDEWriteCommand(CommandPort, Command);
    StallExecutionProcessor(50);

    /* Wait for DRQ or error */
    for (RetryCount = 0; RetryCount < IDE_MAX_POLL_RETRIES; RetryCount++)
    {
        Status = IDEReadStatus(CommandPort);
        if (!(Status & IDE_SR_BUSY))
        {
            if (Status & IDE_SR_ERR)
            {
                IDEWriteDriveControl(ControlPort, 0);
                StallExecutionProcessor(50);
                IDEReadStatus(CommandPort);
                return FALSE;
            }

            if (Status & IDE_SR_DRQ)
            {
                break;
            }
            else
            {
                IDEWriteDriveControl(ControlPort, 0);
                StallExecutionProcessor(50);
                IDEReadStatus(CommandPort);
                return FALSE;
            }
        }
        StallExecutionProcessor(10);
    }

    /* Timed out */
    if (RetryCount >= IDE_MAX_POLL_RETRIES)
    {
        IDEWriteDriveControl(ControlPort, 0);
        StallExecutionProcessor(50);
        IDEReadStatus(CommandPort);
        return FALSE;
    }

    while (1)
    {
        /* Read data into buffer */
        if (Junk == FALSE)
        {
            IDEReadBlock(CommandPort, Buffer, IDE_SECTOR_BUF_SZ);
            Buffer = (PVOID)((ULONG_PTR)Buffer + IDE_SECTOR_BUF_SZ);
        }
        else
        {
            UCHAR JunkBuffer[IDE_SECTOR_BUF_SZ];
            IDEReadBlock(CommandPort, JunkBuffer, IDE_SECTOR_BUF_SZ);
        }
        SectorCount++;

        /* Check for error or more sectors to read */
        for (RetryCount = 0; RetryCount < IDE_MAX_BUSY_RETRIES; RetryCount++)
        {
            Status = IDEReadStatus(CommandPort);
            if (!(Status & IDE_SR_BUSY))
            {
                if (Status & IDE_SR_ERR)
                {
                    IDEWriteDriveControl(ControlPort, 0);
                    StallExecutionProcessor(50);
                    IDEReadStatus(CommandPort);
                    return FALSE;
                }
                if (Status & IDE_SR_DRQ)
                {
                    if (SectorCount >= SectorCnt)
                    {
                        TRACE("Buffer size exceeded!\n");
                        Junk = TRUE;
                    }
                    break;
                }
                else
                {
                    if (SectorCount > SectorCnt)
                    {
                        TRACE("Read %lu sectors of junk!\n",
                              SectorCount - SectorCnt);
                    }

                    IDEWriteDriveControl(ControlPort, 0);
                    StallExecutionProcessor(50);
                    IDEReadStatus(CommandPort);
                    return TRUE;
                }
            }
        }
    }
}