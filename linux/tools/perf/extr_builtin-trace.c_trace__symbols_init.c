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
struct TYPE_3__ {int /*<<< orphan*/  target; } ;
struct trace {TYPE_1__ opts; int /*<<< orphan*/  tool; int /*<<< orphan*/ * host; } ;
struct TYPE_4__ {int /*<<< orphan*/  threads; } ;
struct evlist {TYPE_2__ core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __machine__synthesize_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * machine__new_host () ; 
 int /*<<< orphan*/  symbol__exit () ; 
 int symbol__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace__machine__resolve_kernel_addr ; 
 int /*<<< orphan*/  trace__tool_process ; 
 int trace_event__register_resolver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace__symbols_init(struct trace *trace, struct evlist *evlist)
{
	int err = symbol__init(NULL);

	if (err)
		return err;

	trace->host = machine__new_host();
	if (trace->host == NULL)
		return -ENOMEM;

	err = trace_event__register_resolver(trace->host, trace__machine__resolve_kernel_addr);
	if (err < 0)
		goto out;

	err = __machine__synthesize_threads(trace->host, &trace->tool, &trace->opts.target,
					    evlist->core.threads, trace__tool_process, false,
					    1);
out:
	if (err)
		symbol__exit();

	return err;
}