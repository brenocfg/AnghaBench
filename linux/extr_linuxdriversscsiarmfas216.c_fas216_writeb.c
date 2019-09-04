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
struct TYPE_4__ {unsigned int io_shift; scalar_t__ io_base; } ;
struct TYPE_5__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void fas216_writeb(FAS216_Info *info, unsigned int reg, unsigned int val)
{
	unsigned int off = reg << info->scsi.io_shift;
	writeb(val, info->scsi.io_base + off);
}