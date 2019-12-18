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
struct TYPE_3__ {int /*<<< orphan*/  checkId; scalar_t__ filterProps; scalar_t__ lzma2Props; } ;
typedef  TYPE_1__ CXzProps ;

/* Variables and functions */
 int /*<<< orphan*/  XZ_CHECK_CRC32 ; 

void XzProps_Init(CXzProps *p)
{
  p->lzma2Props = 0;
  p->filterProps = 0;
  p->checkId = XZ_CHECK_CRC32;
}