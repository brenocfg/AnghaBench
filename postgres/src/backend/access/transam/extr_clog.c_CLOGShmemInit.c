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
struct TYPE_3__ {int /*<<< orphan*/  PagePrecedes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOGPagePrecedes ; 
 int /*<<< orphan*/  CLOGShmemBuffers () ; 
 int /*<<< orphan*/  CLOG_LSNS_PER_PAGE ; 
 int /*<<< orphan*/  CLogControlLock ; 
 TYPE_1__* ClogCtl ; 
 int /*<<< orphan*/  LWTRANCHE_CLOG_BUFFERS ; 
 int /*<<< orphan*/  SimpleLruInit (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
CLOGShmemInit(void)
{
	ClogCtl->PagePrecedes = CLOGPagePrecedes;
	SimpleLruInit(ClogCtl, "clog", CLOGShmemBuffers(), CLOG_LSNS_PER_PAGE,
				  CLogControlLock, "pg_xact", LWTRANCHE_CLOG_BUFFERS);
}