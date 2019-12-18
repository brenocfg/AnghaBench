#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ptrdiff_t ;
struct TYPE_6__ {scalar_t__ dirty; scalar_t__ favorDecSpeed; int /*<<< orphan*/ * dictCtx; int /*<<< orphan*/ * base; int /*<<< orphan*/  const* end; } ;
struct TYPE_7__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_2__ LZ4_streamHC_t ;
typedef  int /*<<< orphan*/  LZ4HC_CCtx_internal ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,TYPE_2__* const,unsigned int) ; 
 int /*<<< orphan*/  LZ4HC_CLEVEL_DEFAULT ; 
 int /*<<< orphan*/  LZ4_STATIC_ASSERT (int) ; 
 int LZ4_STREAMHCSIZE ; 
 int /*<<< orphan*/  LZ4_setCompressionLevel (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int LZ4_streamHC_t_alignment () ; 

LZ4_streamHC_t* LZ4_initStreamHC (void* buffer, size_t size)
{
    LZ4_streamHC_t* const LZ4_streamHCPtr = (LZ4_streamHC_t*)buffer;
    if (buffer == NULL) return NULL;
    if (size < sizeof(LZ4_streamHC_t)) return NULL;
#ifndef _MSC_VER  /* for some reason, Visual fails the aligment test on 32-bit x86 :
                   * it reports an aligment of 8-bytes,
                   * while actually aligning LZ4_streamHC_t on 4 bytes. */
    if (((size_t)buffer) & (LZ4_streamHC_t_alignment() - 1)) return NULL;  /* alignment check */
#endif
    /* if compilation fails here, LZ4_STREAMHCSIZE must be increased */
    LZ4_STATIC_ASSERT(sizeof(LZ4HC_CCtx_internal) <= LZ4_STREAMHCSIZE);
    DEBUGLOG(4, "LZ4_initStreamHC(%p, %u)", LZ4_streamHCPtr, (unsigned)size);
    /* end-base will trigger a clearTable on starting compression */
    LZ4_streamHCPtr->internal_donotuse.end = (const BYTE *)(ptrdiff_t)-1;
    LZ4_streamHCPtr->internal_donotuse.base = NULL;
    LZ4_streamHCPtr->internal_donotuse.dictCtx = NULL;
    LZ4_streamHCPtr->internal_donotuse.favorDecSpeed = 0;
    LZ4_streamHCPtr->internal_donotuse.dirty = 0;
    LZ4_setCompressionLevel(LZ4_streamHCPtr, LZ4HC_CLEVEL_DEFAULT);
    return LZ4_streamHCPtr;
}