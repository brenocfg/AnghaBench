#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createDDict_advanced (void const*,size_t,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_initStack (void*,size_t) ; 

ZSTD_DDict *ZSTD_initDDict(const void *dict, size_t dictSize, void *workspace, size_t workspaceSize)
{
	ZSTD_customMem const stackMem = ZSTD_initStack(workspace, workspaceSize);
	return ZSTD_createDDict_advanced(dict, dictSize, 1, stackMem);
}