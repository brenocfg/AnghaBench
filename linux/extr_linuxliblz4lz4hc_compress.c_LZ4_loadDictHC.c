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
struct TYPE_7__ {int /*<<< orphan*/  const* end; } ;
struct TYPE_6__ {TYPE_2__ internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamHC_t ;
typedef  TYPE_2__ LZ4HC_CCtx_internal ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int KB ; 
 int /*<<< orphan*/  LZ4HC_Insert (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LZ4HC_init (TYPE_2__*,int /*<<< orphan*/  const*) ; 

int LZ4_loadDictHC(LZ4_streamHC_t *LZ4_streamHCPtr,
	const char *dictionary,
	int dictSize)
{
	LZ4HC_CCtx_internal *ctxPtr = &LZ4_streamHCPtr->internal_donotuse;

	if (dictSize > 64 * KB) {
		dictionary += dictSize - 64 * KB;
		dictSize = 64 * KB;
	}
	LZ4HC_init(ctxPtr, (const BYTE *)dictionary);
	if (dictSize >= 4)
		LZ4HC_Insert(ctxPtr, (const BYTE *)dictionary + (dictSize - 3));
	ctxPtr->end = (const BYTE *)dictionary + dictSize;
	return dictSize;
}