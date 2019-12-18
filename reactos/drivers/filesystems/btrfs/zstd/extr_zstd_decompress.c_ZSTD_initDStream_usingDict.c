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
struct TYPE_4__ {scalar_t__ noForwardProgress; int /*<<< orphan*/  streamStage; } ;
typedef  TYPE_1__ ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  ZSTD_DCtx_loadDictionary (TYPE_1__*,void const*,size_t) ; 
 size_t ZSTD_frameHeaderSize_prefix ; 
 int /*<<< orphan*/  zdss_init ; 

size_t ZSTD_initDStream_usingDict(ZSTD_DStream* zds, const void* dict, size_t dictSize)
{
    DEBUGLOG(4, "ZSTD_initDStream_usingDict");
    zds->streamStage = zdss_init;
    zds->noForwardProgress = 0;
    CHECK_F( ZSTD_DCtx_loadDictionary(zds, dict, dictSize) );
    return ZSTD_frameHeaderSize_prefix;
}