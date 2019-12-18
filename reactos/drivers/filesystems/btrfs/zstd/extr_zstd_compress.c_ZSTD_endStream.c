#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ pos; scalar_t__ size; } ;
typedef  TYPE_3__ ZSTD_outBuffer ;
struct TYPE_14__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ ZSTD_inBuffer ;
struct TYPE_11__ {int checksumFlag; } ;
struct TYPE_12__ {TYPE_1__ fParams; } ;
struct TYPE_15__ {size_t const outBuffContentSize; size_t const outBuffFlushedSize; TYPE_2__ appliedParams; scalar_t__ frameEnded; } ;
typedef  TYPE_5__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 size_t ZSTD_BLOCKHEADERSIZE ; 
 int /*<<< orphan*/  ZSTD_compressStream_generic (TYPE_5__*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_e_end ; 

size_t ZSTD_endStream(ZSTD_CStream* zcs, ZSTD_outBuffer* output)
{
    ZSTD_inBuffer input = { NULL, 0, 0 };
    if (output->pos > output->size) return ERROR(GENERIC);
    CHECK_F( ZSTD_compressStream_generic(zcs, output, &input, ZSTD_e_end) );
    {   size_t const lastBlockSize = zcs->frameEnded ? 0 : ZSTD_BLOCKHEADERSIZE;
        size_t const checksumSize = zcs->frameEnded ? 0 : zcs->appliedParams.fParams.checksumFlag * 4;
        size_t const toFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize + lastBlockSize + checksumSize;
        DEBUGLOG(4, "ZSTD_endStream : remaining to flush : %u", (U32)toFlush);
        return toFlush;
    }
}