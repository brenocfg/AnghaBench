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
struct TYPE_4__ {int /*<<< orphan*/  const* ddict; } ;
typedef  TYPE_1__ ZSTD_DStream ;
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 TYPE_1__* ZSTD_initDStream (size_t,void*,size_t) ; 

ZSTD_DStream *ZSTD_initDStream_usingDDict(size_t maxWindowSize, const ZSTD_DDict *ddict, void *workspace, size_t workspaceSize)
{
	ZSTD_DStream *zds = ZSTD_initDStream(maxWindowSize, workspace, workspaceSize);
	if (zds) {
		zds->ddict = ddict;
	}
	return zds;
}