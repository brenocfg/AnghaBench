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
struct TYPE_7__ {TYPE_2__* SCpnt; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {char id; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */

__attribute__((used)) static char fas216_target(FAS216_Info *info)
{
	if (info->SCpnt)
		return '0' + info->SCpnt->device->id;
	else
		return 'H';
}