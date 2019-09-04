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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_4__ {struct TYPE_4__* outBuff; struct TYPE_4__* inBuff; int /*<<< orphan*/ * ddictLocal; int /*<<< orphan*/ * dctx; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_1__ ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeDDict (int /*<<< orphan*/ *) ; 

size_t ZSTD_freeDStream(ZSTD_DStream *zds)
{
	if (zds == NULL)
		return 0; /* support free on null */
	{
		ZSTD_customMem const cMem = zds->customMem;
		ZSTD_freeDCtx(zds->dctx);
		zds->dctx = NULL;
		ZSTD_freeDDict(zds->ddictLocal);
		zds->ddictLocal = NULL;
		ZSTD_free(zds->inBuff, cMem);
		zds->inBuff = NULL;
		ZSTD_free(zds->outBuff, cMem);
		zds->outBuff = NULL;
		ZSTD_free(zds, cMem);
		return 0;
	}
}