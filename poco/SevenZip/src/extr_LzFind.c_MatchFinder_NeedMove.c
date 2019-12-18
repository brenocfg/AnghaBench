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
struct TYPE_3__ {size_t keepSizeAfter; scalar_t__ buffer; scalar_t__ blockSize; scalar_t__ bufferBase; scalar_t__ directInput; } ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */

int MatchFinder_NeedMove(CMatchFinder *p)
{
  if (p->directInput)
    return 0;
  /* if (p->streamEndWasReached) return 0; */
  return ((size_t)(p->bufferBase + p->blockSize - p->buffer) <= p->keepSizeAfter);
}