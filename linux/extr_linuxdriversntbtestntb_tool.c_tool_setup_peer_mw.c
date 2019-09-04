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
typedef  int /*<<< orphan*/  u64 ;
struct tool_mw {size_t size; int pidx; int /*<<< orphan*/  dbgfs_file; int /*<<< orphan*/  tr_base; int /*<<< orphan*/ * io_base; } ;
struct tool_ctx {int /*<<< orphan*/  ntb; TYPE_1__* peers; struct tool_mw* outmws; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dbgfs_dir; } ;

/* Variables and functions */
 int EFAULT ; 
 int TOOL_BUF_LEN ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct tool_mw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ioremap_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_peer_mw_clear_trans (int /*<<< orphan*/ ,int,int) ; 
 int ntb_peer_mw_get_addr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_peer_mw_set_trans (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tool_peer_mw_fops ; 

__attribute__((used)) static int tool_setup_peer_mw(struct tool_ctx *tc, int pidx, int widx,
			      u64 req_addr, size_t req_size)
{
	struct tool_mw *outmw = &tc->outmws[widx];
	resource_size_t map_size;
	phys_addr_t map_base;
	char buf[TOOL_BUF_LEN];
	int ret;

	if (outmw->io_base != NULL)
		return 0;

	ret = ntb_peer_mw_get_addr(tc->ntb, widx, &map_base, &map_size);
	if (ret)
		return ret;

	ret = ntb_peer_mw_set_trans(tc->ntb, pidx, widx, req_addr, req_size);
	if (ret)
		return ret;

	outmw->io_base = ioremap_wc(map_base, map_size);
	if (outmw->io_base == NULL) {
		ret = -EFAULT;
		goto err_clear_trans;
	}

	outmw->tr_base = req_addr;
	outmw->size = req_size;
	outmw->pidx = pidx;

	snprintf(buf, sizeof(buf), "peer_mw%d", widx);
	outmw->dbgfs_file = debugfs_create_file(buf, 0600,
					       tc->peers[pidx].dbgfs_dir, outmw,
					       &tool_peer_mw_fops);

	return 0;

err_clear_trans:
	ntb_peer_mw_clear_trans(tc->ntb, pidx, widx);

	return ret;
}