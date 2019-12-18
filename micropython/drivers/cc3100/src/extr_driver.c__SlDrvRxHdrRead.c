#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int _u8 ;
typedef  size_t _u32 ;
typedef  size_t _u16 ;
typedef  int /*<<< orphan*/  _SlReturnVal_t ;
struct TYPE_6__ {int /*<<< orphan*/  DoubleSyncPattern; } ;
struct TYPE_5__ {int /*<<< orphan*/  Short; } ;
struct TYPE_4__ {int /*<<< orphan*/  FD; int /*<<< orphan*/  TxSeqNum; } ;

/* Variables and functions */
 scalar_t__ N2H_SYNC_PATTERN_MATCH (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NWP_IF_READ_CHECK (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  NWP_IF_WRITE_CHECK (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  SL_RET_CODE_OK ; 
 size_t SL_SYNC_SCAN_THRESHOLD ; 
 size_t SYNC_PATTERN_LEN ; 
 int /*<<< orphan*/  VERIFY_PROTOCOL (int) ; 
 TYPE_3__ Work ; 
 int /*<<< orphan*/  _SL_DBG_CNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SL_DBG_SYNC_LOG (size_t,int*) ; 
 size_t _SL_RESP_SPEC_HDR_SIZE ; 
 TYPE_2__ g_H2NCnysPattern ; 
 TYPE_1__* g_pCB ; 

_SlReturnVal_t   _SlDrvRxHdrRead(_u8 *pBuf, _u8 *pAlignSize)
{
     _u32       SyncCnt  = 0;
    _u8        ShiftIdx;  

#ifndef SL_IF_TYPE_UART
    /*  1. Write CNYS pattern to NWP when working in SPI mode only  */
    NWP_IF_WRITE_CHECK(g_pCB->FD, (_u8 *)&g_H2NCnysPattern.Short, SYNC_PATTERN_LEN);
#endif

    /*  2. Read 4 bytes (protocol aligned) */
    NWP_IF_READ_CHECK(g_pCB->FD, &pBuf[0], 4);
    _SL_DBG_SYNC_LOG(SyncCnt,pBuf);

    /* Wait for SYNC_PATTERN_LEN from the device */
    while ( ! N2H_SYNC_PATTERN_MATCH(pBuf, g_pCB->TxSeqNum) )
    {
        /*  3. Debug limit of scan */
        VERIFY_PROTOCOL(SyncCnt < SL_SYNC_SCAN_THRESHOLD);

        /*  4. Read next 4 bytes to Low 4 bytes of buffer */
        if(0 == (SyncCnt % (_u32)SYNC_PATTERN_LEN))
        {
            NWP_IF_READ_CHECK(g_pCB->FD, &pBuf[4], 4);
            _SL_DBG_SYNC_LOG(SyncCnt,pBuf);
        }

        /*  5. Shift Buffer Up for checking if the sync is shifted */
        for(ShiftIdx = 0; ShiftIdx< 7; ShiftIdx++)
        {
            pBuf[ShiftIdx] = pBuf[ShiftIdx+1];
        }             
        pBuf[7] = 0;

        SyncCnt++;
    }

    /*  5. Sync pattern found. If needed, complete number of read bytes to multiple of 4 (protocol align) */
    SyncCnt %= SYNC_PATTERN_LEN;

    if(SyncCnt > 0)
    {
        *(_u32 *)&pBuf[0] = *(_u32 *)&pBuf[4];
        NWP_IF_READ_CHECK(g_pCB->FD, &pBuf[SYNC_PATTERN_LEN - SyncCnt], (_u16)SyncCnt);
    }
    else
    {
        NWP_IF_READ_CHECK(g_pCB->FD, &pBuf[0], 4);
    }

    /*  6. Scan for Double pattern. */
    while ( N2H_SYNC_PATTERN_MATCH(pBuf, g_pCB->TxSeqNum) )
    {
        _SL_DBG_CNT_INC(Work.DoubleSyncPattern);
        NWP_IF_READ_CHECK(g_pCB->FD, &pBuf[0], SYNC_PATTERN_LEN);
    }
    g_pCB->TxSeqNum++;

    /*  7. Here we've read Generic Header (4 bytes). Read the Resp Specific header (4 more bytes). */
    NWP_IF_READ_CHECK(g_pCB->FD, &pBuf[SYNC_PATTERN_LEN], _SL_RESP_SPEC_HDR_SIZE);

    /*  8. Here we've read the entire Resp Header. */
    /*     Return number bytes needed to be sent after read for NWP Rx 4-byte alignment (protocol alignment) */
    *pAlignSize = (_u8)((SyncCnt > 0) ? (SYNC_PATTERN_LEN - SyncCnt) : 0);

    return SL_RET_CODE_OK;
}