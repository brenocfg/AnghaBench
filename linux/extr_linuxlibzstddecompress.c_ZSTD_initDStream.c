#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_5__ {size_t maxWindowSize; char* inBuff; size_t inBuffSize; char* outBuff; size_t outBuffSize; int /*<<< orphan*/  customMem; scalar_t__ hostageByte; scalar_t__ legacyVersion; int /*<<< orphan*/ * ddictLocal; int /*<<< orphan*/ * ddict; scalar_t__ outEnd; scalar_t__ outStart; scalar_t__ inPos; scalar_t__ lhSize; int /*<<< orphan*/  stage; } ;
typedef  TYPE_1__ ZSTD_DStream ;

/* Variables and functions */
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int WILDCOPY_OVERLENGTH ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_ABSOLUTEMAX ; 
 TYPE_1__* ZSTD_createDStream_advanced (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_freeDDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_initStack (void*,size_t) ; 
 scalar_t__ ZSTD_malloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdss_loadHeader ; 

ZSTD_DStream *ZSTD_initDStream(size_t maxWindowSize, void *workspace, size_t workspaceSize)
{
	ZSTD_customMem const stackMem = ZSTD_initStack(workspace, workspaceSize);
	ZSTD_DStream *zds = ZSTD_createDStream_advanced(stackMem);
	if (!zds) {
		return NULL;
	}

	zds->maxWindowSize = maxWindowSize;
	zds->stage = zdss_loadHeader;
	zds->lhSize = zds->inPos = zds->outStart = zds->outEnd = 0;
	ZSTD_freeDDict(zds->ddictLocal);
	zds->ddictLocal = NULL;
	zds->ddict = zds->ddictLocal;
	zds->legacyVersion = 0;
	zds->hostageByte = 0;

	{
		size_t const blockSize = MIN(zds->maxWindowSize, ZSTD_BLOCKSIZE_ABSOLUTEMAX);
		size_t const neededOutSize = zds->maxWindowSize + blockSize + WILDCOPY_OVERLENGTH * 2;

		zds->inBuff = (char *)ZSTD_malloc(blockSize, zds->customMem);
		zds->inBuffSize = blockSize;
		zds->outBuff = (char *)ZSTD_malloc(neededOutSize, zds->customMem);
		zds->outBuffSize = neededOutSize;
		if (zds->inBuff == NULL || zds->outBuff == NULL) {
			ZSTD_freeDStream(zds);
			return NULL;
		}
	}
	return zds;
}