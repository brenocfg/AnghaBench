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
struct TYPE_3__ {int /*<<< orphan*/ * hj_CurTuple; scalar_t__ hj_CurSkewBucketNo; scalar_t__ hj_CurBucketNo; } ;
typedef  TYPE_1__ HashJoinState ;

/* Variables and functions */

void
ExecPrepHashTableForUnmatched(HashJoinState *hjstate)
{
	/*----------
	 * During this scan we use the HashJoinState fields as follows:
	 *
	 * hj_CurBucketNo: next regular bucket to scan
	 * hj_CurSkewBucketNo: next skew bucket (an index into skewBucketNums)
	 * hj_CurTuple: last tuple returned, or NULL to start next bucket
	 *----------
	 */
	hjstate->hj_CurBucketNo = 0;
	hjstate->hj_CurSkewBucketNo = 0;
	hjstate->hj_CurTuple = NULL;
}