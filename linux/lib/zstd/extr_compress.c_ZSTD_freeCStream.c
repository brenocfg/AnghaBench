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
struct TYPE_4__ {struct TYPE_4__* outBuff; struct TYPE_4__* inBuff; int /*<<< orphan*/ * cdictLocal; int /*<<< orphan*/ * cctx; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_1__ ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeCDict (int /*<<< orphan*/ *) ; 

size_t ZSTD_freeCStream(ZSTD_CStream *zcs)
{
	if (zcs == NULL)
		return 0; /* support free on NULL */
	{
		ZSTD_customMem const cMem = zcs->customMem;
		ZSTD_freeCCtx(zcs->cctx);
		zcs->cctx = NULL;
		ZSTD_freeCDict(zcs->cdictLocal);
		zcs->cdictLocal = NULL;
		ZSTD_free(zcs->inBuff, cMem);
		zcs->inBuff = NULL;
		ZSTD_free(zcs->outBuff, cMem);
		zcs->outBuff = NULL;
		ZSTD_free(zcs, cMem);
		return 0;
	}
}