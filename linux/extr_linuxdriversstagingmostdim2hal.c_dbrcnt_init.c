#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rpc; int /*<<< orphan*/  wpc; int /*<<< orphan*/  rest_size; } ;
struct TYPE_4__ {TYPE_1__ atx_dbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dim2_rpc (int /*<<< orphan*/ ) ; 
 TYPE_2__ g ; 

__attribute__((used)) static void dbrcnt_init(u8 ch_addr, u16 dbr_size)
{
	g.atx_dbr.rest_size = dbr_size;
	g.atx_dbr.rpc = dim2_rpc(ch_addr);
	g.atx_dbr.wpc = g.atx_dbr.rpc;
}