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
typedef  scalar_t__ UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/  streamPos; int /*<<< orphan*/  pos; int /*<<< orphan*/  posLimit; } ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */

void MatchFinder_ReduceOffsets(CMatchFinder *p, UInt32 subValue)
{
  p->posLimit -= subValue;
  p->pos -= subValue;
  p->streamPos -= subValue;
}