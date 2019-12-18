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
struct perf_event_attr {int dummy; } ;
typedef  int /*<<< orphan*/  attr__fprintf_f ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  PRINT_ATTRf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ATTRn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aux_output ; 
 int /*<<< orphan*/  aux_watermark ; 
 int /*<<< orphan*/  bp_addr ; 
 int /*<<< orphan*/  bp_len ; 
 int /*<<< orphan*/  bp_type ; 
 int /*<<< orphan*/  bpf_event ; 
 int /*<<< orphan*/  branch_sample_type ; 
 int /*<<< orphan*/  clockid ; 
 int /*<<< orphan*/  comm ; 
 int /*<<< orphan*/  comm_exec ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  context_switch ; 
 int /*<<< orphan*/  disabled ; 
 int /*<<< orphan*/  enable_on_exec ; 
 int /*<<< orphan*/  exclude_callchain_kernel ; 
 int /*<<< orphan*/  exclude_callchain_user ; 
 int /*<<< orphan*/  exclude_guest ; 
 int /*<<< orphan*/  exclude_host ; 
 int /*<<< orphan*/  exclude_hv ; 
 int /*<<< orphan*/  exclude_idle ; 
 int /*<<< orphan*/  exclude_kernel ; 
 int /*<<< orphan*/  exclude_user ; 
 int /*<<< orphan*/  exclusive ; 
 int /*<<< orphan*/  freq ; 
 int /*<<< orphan*/  inherit ; 
 int /*<<< orphan*/  inherit_stat ; 
 int /*<<< orphan*/  ksymbol ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  mmap2 ; 
 int /*<<< orphan*/  mmap_data ; 
 int /*<<< orphan*/  namespaces ; 
 int /*<<< orphan*/  p_branch_sample_type ; 
 int /*<<< orphan*/  p_hex ; 
 int /*<<< orphan*/  p_read_format ; 
 int /*<<< orphan*/  p_sample_type ; 
 int /*<<< orphan*/  p_signed ; 
 int /*<<< orphan*/  p_unsigned ; 
 int /*<<< orphan*/  pinned ; 
 int /*<<< orphan*/  precise_ip ; 
 int /*<<< orphan*/  read_format ; 
 int /*<<< orphan*/  sample_id_all ; 
 int /*<<< orphan*/  sample_max_stack ; 
 int /*<<< orphan*/  sample_period ; 
 int /*<<< orphan*/  sample_regs_intr ; 
 int /*<<< orphan*/  sample_regs_user ; 
 int /*<<< orphan*/  sample_stack_user ; 
 int /*<<< orphan*/  sample_type ; 
 int /*<<< orphan*/  size ; 
 int /*<<< orphan*/  task ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  use_clockid ; 
 int /*<<< orphan*/  wakeup_events ; 
 int /*<<< orphan*/  watermark ; 
 int /*<<< orphan*/  write_backward ; 

int perf_event_attr__fprintf(FILE *fp, struct perf_event_attr *attr,
			     attr__fprintf_f attr__fprintf, void *priv)
{
	char buf[BUF_SIZE];
	int ret = 0;

	PRINT_ATTRf(type, p_unsigned);
	PRINT_ATTRf(size, p_unsigned);
	PRINT_ATTRf(config, p_hex);
	PRINT_ATTRn("{ sample_period, sample_freq }", sample_period, p_unsigned);
	PRINT_ATTRf(sample_type, p_sample_type);
	PRINT_ATTRf(read_format, p_read_format);

	PRINT_ATTRf(disabled, p_unsigned);
	PRINT_ATTRf(inherit, p_unsigned);
	PRINT_ATTRf(pinned, p_unsigned);
	PRINT_ATTRf(exclusive, p_unsigned);
	PRINT_ATTRf(exclude_user, p_unsigned);
	PRINT_ATTRf(exclude_kernel, p_unsigned);
	PRINT_ATTRf(exclude_hv, p_unsigned);
	PRINT_ATTRf(exclude_idle, p_unsigned);
	PRINT_ATTRf(mmap, p_unsigned);
	PRINT_ATTRf(comm, p_unsigned);
	PRINT_ATTRf(freq, p_unsigned);
	PRINT_ATTRf(inherit_stat, p_unsigned);
	PRINT_ATTRf(enable_on_exec, p_unsigned);
	PRINT_ATTRf(task, p_unsigned);
	PRINT_ATTRf(watermark, p_unsigned);
	PRINT_ATTRf(precise_ip, p_unsigned);
	PRINT_ATTRf(mmap_data, p_unsigned);
	PRINT_ATTRf(sample_id_all, p_unsigned);
	PRINT_ATTRf(exclude_host, p_unsigned);
	PRINT_ATTRf(exclude_guest, p_unsigned);
	PRINT_ATTRf(exclude_callchain_kernel, p_unsigned);
	PRINT_ATTRf(exclude_callchain_user, p_unsigned);
	PRINT_ATTRf(mmap2, p_unsigned);
	PRINT_ATTRf(comm_exec, p_unsigned);
	PRINT_ATTRf(use_clockid, p_unsigned);
	PRINT_ATTRf(context_switch, p_unsigned);
	PRINT_ATTRf(write_backward, p_unsigned);
	PRINT_ATTRf(namespaces, p_unsigned);
	PRINT_ATTRf(ksymbol, p_unsigned);
	PRINT_ATTRf(bpf_event, p_unsigned);
	PRINT_ATTRf(aux_output, p_unsigned);

	PRINT_ATTRn("{ wakeup_events, wakeup_watermark }", wakeup_events, p_unsigned);
	PRINT_ATTRf(bp_type, p_unsigned);
	PRINT_ATTRn("{ bp_addr, config1 }", bp_addr, p_hex);
	PRINT_ATTRn("{ bp_len, config2 }", bp_len, p_hex);
	PRINT_ATTRf(branch_sample_type, p_branch_sample_type);
	PRINT_ATTRf(sample_regs_user, p_hex);
	PRINT_ATTRf(sample_stack_user, p_unsigned);
	PRINT_ATTRf(clockid, p_signed);
	PRINT_ATTRf(sample_regs_intr, p_hex);
	PRINT_ATTRf(aux_watermark, p_unsigned);
	PRINT_ATTRf(sample_max_stack, p_unsigned);

	return ret;
}