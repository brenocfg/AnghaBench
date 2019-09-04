#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int hashLog; scalar_t__ strategy; int chainLog; } ;
struct TYPE_6__ {TYPE_1__ cParams; } ;
struct TYPE_7__ {int hashLog3; int /*<<< orphan*/  hashTable3; int /*<<< orphan*/  chainTable; TYPE_2__ params; int /*<<< orphan*/  hashTable; } ;
typedef  TYPE_3__ ZSTD_CCtx ;
typedef  int U32 ;

/* Variables and functions */
 scalar_t__ ZSTD_fast ; 
 int /*<<< orphan*/  ZSTD_reduceTable (int /*<<< orphan*/ ,int const,int const) ; 

__attribute__((used)) static void ZSTD_reduceIndex(ZSTD_CCtx *zc, const U32 reducerValue)
{
	{
		U32 const hSize = 1 << zc->params.cParams.hashLog;
		ZSTD_reduceTable(zc->hashTable, hSize, reducerValue);
	}

	{
		U32 const chainSize = (zc->params.cParams.strategy == ZSTD_fast) ? 0 : (1 << zc->params.cParams.chainLog);
		ZSTD_reduceTable(zc->chainTable, chainSize, reducerValue);
	}

	{
		U32 const h3Size = (zc->hashLog3) ? 1 << zc->hashLog3 : 0;
		ZSTD_reduceTable(zc->hashTable3, h3Size, reducerValue);
	}
}