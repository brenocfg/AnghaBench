#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tool_ctx {int outmw_cnt; int peer_cnt; TYPE_1__* peers; } ;
struct TYPE_2__ {int inmw_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  tool_free_mw (struct tool_ctx*,int,int) ; 
 int /*<<< orphan*/  tool_free_peer_mw (struct tool_ctx*,int) ; 

__attribute__((used)) static void tool_clear_mws(struct tool_ctx *tc)
{
	int widx, pidx;

	/* Free outbound memory windows */
	for (widx = 0; widx < tc->outmw_cnt; widx++)
		tool_free_peer_mw(tc, widx);

	/* Free outbound memory windows */
	for (pidx = 0; pidx < tc->peer_cnt; pidx++)
		for (widx = 0; widx < tc->peers[pidx].inmw_cnt; widx++)
			tool_free_mw(tc, pidx, widx);
}