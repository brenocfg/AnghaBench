#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct bpf_raw_tracepoint* private_data; } ;
struct bpf_raw_tracepoint {int /*<<< orphan*/  btp; scalar_t__ prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_probe_unregister (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bpf_prog_put (scalar_t__) ; 
 int /*<<< orphan*/  bpf_put_raw_tracepoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bpf_raw_tracepoint*) ; 

__attribute__((used)) static int bpf_raw_tracepoint_release(struct inode *inode, struct file *filp)
{
	struct bpf_raw_tracepoint *raw_tp = filp->private_data;

	if (raw_tp->prog) {
		bpf_probe_unregister(raw_tp->btp, raw_tp->prog);
		bpf_prog_put(raw_tp->prog);
	}
	bpf_put_raw_tracepoint(raw_tp->btp);
	kfree(raw_tp);
	return 0;
}