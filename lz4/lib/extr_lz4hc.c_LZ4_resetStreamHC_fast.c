#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uptrval ;
struct TYPE_7__ {int /*<<< orphan*/ * dictCtx; int /*<<< orphan*/ * base; int /*<<< orphan*/  end; scalar_t__ dirty; } ;
struct TYPE_8__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_2__ LZ4_streamHC_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  LZ4_initStreamHC (TYPE_2__*,int) ; 
 int /*<<< orphan*/  LZ4_setCompressionLevel (TYPE_2__*,int) ; 

void LZ4_resetStreamHC_fast (LZ4_streamHC_t* LZ4_streamHCPtr, int compressionLevel)
{
    DEBUGLOG(4, "LZ4_resetStreamHC_fast(%p, %d)", LZ4_streamHCPtr, compressionLevel);
    if (LZ4_streamHCPtr->internal_donotuse.dirty) {
        LZ4_initStreamHC(LZ4_streamHCPtr, sizeof(*LZ4_streamHCPtr));
    } else {
        /* preserve end - base : can trigger clearTable's threshold */
        LZ4_streamHCPtr->internal_donotuse.end -= (uptrval)LZ4_streamHCPtr->internal_donotuse.base;
        LZ4_streamHCPtr->internal_donotuse.base = NULL;
        LZ4_streamHCPtr->internal_donotuse.dictCtx = NULL;
    }
    LZ4_setCompressionLevel(LZ4_streamHCPtr, compressionLevel);
}