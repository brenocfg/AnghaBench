#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int directInput; int /*<<< orphan*/  directInputRem; int /*<<< orphan*/ * bufferBase; } ;
struct TYPE_5__ {TYPE_1__ matchFinderBase; } ;
typedef  int /*<<< orphan*/  SizeT ;
typedef  TYPE_2__ CLzmaEnc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */

__attribute__((used)) static void LzmaEnc_SetInputBuf(CLzmaEnc *p, const Byte *src, SizeT srcLen)
{
  p->matchFinderBase.directInput = 1;
  p->matchFinderBase.bufferBase = (Byte *)src;
  p->matchFinderBase.directInputRem = srcLen;
}