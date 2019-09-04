#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* chainTable; int nextToUpdate; int dictLimit; int lowLimit; int /*<<< orphan*/  const* dictBase; int /*<<< orphan*/  const* end; int /*<<< orphan*/  const* base; scalar_t__ hashTable; } ;
typedef  TYPE_1__ LZ4HC_CCtx_internal ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int KB ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 

__attribute__((used)) static void LZ4HC_init(LZ4HC_CCtx_internal *hc4, const BYTE *start)
{
	memset((void *)hc4->hashTable, 0, sizeof(hc4->hashTable));
	memset(hc4->chainTable, 0xFF, sizeof(hc4->chainTable));
	hc4->nextToUpdate = 64 * KB;
	hc4->base = start - 64 * KB;
	hc4->end = start;
	hc4->dictBase = start - 64 * KB;
	hc4->dictLimit = 64 * KB;
	hc4->lowLimit = 64 * KB;
}