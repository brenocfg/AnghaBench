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
struct rproc_mem_entry {int /*<<< orphan*/  node; int /*<<< orphan*/ * va; int /*<<< orphan*/  priv; int /*<<< orphan*/  len; } ;
struct device {int dummy; } ;
struct rproc {int num_traces; int /*<<< orphan*/  traces; struct device dev; } ;
struct fw_rsc_trace {int /*<<< orphan*/  len; int /*<<< orphan*/  da; scalar_t__ reserved; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct rproc_mem_entry*) ; 
 struct rproc_mem_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_create_trace_file (char*,struct rproc*,struct rproc_mem_entry*) ; 
 void* rproc_da_to_va (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int rproc_handle_trace(struct rproc *rproc, struct fw_rsc_trace *rsc,
			      int offset, int avail)
{
	struct rproc_mem_entry *trace;
	struct device *dev = &rproc->dev;
	void *ptr;
	char name[15];

	if (sizeof(*rsc) > avail) {
		dev_err(dev, "trace rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved) {
		dev_err(dev, "trace rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	/* what's the kernel address of this resource ? */
	ptr = rproc_da_to_va(rproc, rsc->da, rsc->len);
	if (!ptr) {
		dev_err(dev, "erroneous trace resource entry\n");
		return -EINVAL;
	}

	trace = kzalloc(sizeof(*trace), GFP_KERNEL);
	if (!trace)
		return -ENOMEM;

	/* set the trace buffer dma properties */
	trace->len = rsc->len;
	trace->va = ptr;

	/* make sure snprintf always null terminates, even if truncating */
	snprintf(name, sizeof(name), "trace%d", rproc->num_traces);

	/* create the debugfs entry */
	trace->priv = rproc_create_trace_file(name, rproc, trace);
	if (!trace->priv) {
		trace->va = NULL;
		kfree(trace);
		return -EINVAL;
	}

	list_add_tail(&trace->node, &rproc->traces);

	rproc->num_traces++;

	dev_dbg(dev, "%s added: va %pK, da 0x%x, len 0x%x\n",
		name, ptr, rsc->da, rsc->len);

	return 0;
}