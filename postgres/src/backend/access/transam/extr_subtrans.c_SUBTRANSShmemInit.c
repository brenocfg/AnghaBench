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
struct TYPE_3__ {int do_fsync; int /*<<< orphan*/  PagePrecedes; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWTRANCHE_SUBTRANS_BUFFERS ; 
 int /*<<< orphan*/  NUM_SUBTRANS_BUFFERS ; 
 int /*<<< orphan*/  SimpleLruInit (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* SubTransCtl ; 
 int /*<<< orphan*/  SubTransPagePrecedes ; 
 int /*<<< orphan*/  SubtransControlLock ; 

void
SUBTRANSShmemInit(void)
{
	SubTransCtl->PagePrecedes = SubTransPagePrecedes;
	SimpleLruInit(SubTransCtl, "subtrans", NUM_SUBTRANS_BUFFERS, 0,
				  SubtransControlLock, "pg_subtrans",
				  LWTRANCHE_SUBTRANS_BUFFERS);
	/* Override default assumption that writes should be fsync'd */
	SubTransCtl->do_fsync = false;
}