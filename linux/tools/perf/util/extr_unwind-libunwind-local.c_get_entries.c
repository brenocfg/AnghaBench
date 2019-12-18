#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unwind_entry_cb_t ;
typedef  scalar_t__ unw_word_t ;
typedef  int /*<<< orphan*/  unw_cursor_t ;
typedef  int /*<<< orphan*/ * unw_addr_space_t ;
typedef  scalar_t__ u64 ;
struct unwind_info {TYPE_3__* thread; TYPE_1__* sample; } ;
struct TYPE_8__ {scalar_t__ order; } ;
struct TYPE_7__ {TYPE_2__* mg; } ;
struct TYPE_6__ {int /*<<< orphan*/ * addr_space; } ;
struct TYPE_5__ {int /*<<< orphan*/  user_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUNWIND__ARCH_REG_IP ; 
 scalar_t__ ORDER_CALLER ; 
 int /*<<< orphan*/  UNW_REG_IP ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 TYPE_4__ callchain_param ; 
 int /*<<< orphan*/  display_error (int) ; 
 int entry (scalar_t__,TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int perf_reg_value (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unw_get_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int unw_init_remote (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct unwind_info*) ; 
 scalar_t__ unw_is_signal_frame (int /*<<< orphan*/ *) ; 
 scalar_t__ unw_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_entries(struct unwind_info *ui, unwind_entry_cb_t cb,
		       void *arg, int max_stack)
{
	u64 val;
	unw_word_t ips[max_stack];
	unw_addr_space_t addr_space;
	unw_cursor_t c;
	int ret, i = 0;

	ret = perf_reg_value(&val, &ui->sample->user_regs,
			     LIBUNWIND__ARCH_REG_IP);
	if (ret)
		return ret;

	ips[i++] = (unw_word_t) val;

	/*
	 * If we need more than one entry, do the DWARF
	 * unwind itself.
	 */
	if (max_stack - 1 > 0) {
		WARN_ONCE(!ui->thread, "WARNING: ui->thread is NULL");
		addr_space = ui->thread->mg->addr_space;

		if (addr_space == NULL)
			return -1;

		ret = unw_init_remote(&c, addr_space, ui);
		if (ret)
			display_error(ret);

		while (!ret && (unw_step(&c) > 0) && i < max_stack) {
			unw_get_reg(&c, UNW_REG_IP, &ips[i]);

			/*
			 * Decrement the IP for any non-activation frames.
			 * this is required to properly find the srcline
			 * for caller frames.
			 * See also the documentation for dwfl_frame_pc(),
			 * which this code tries to replicate.
			 */
			if (unw_is_signal_frame(&c) <= 0)
				--ips[i];

			++i;
		}

		max_stack = i;
	}

	/*
	 * Display what we got based on the order setup.
	 */
	for (i = 0; i < max_stack && !ret; i++) {
		int j = i;

		if (callchain_param.order == ORDER_CALLER)
			j = max_stack - i - 1;
		ret = ips[j] ? entry(ips[j], ui->thread, cb, arg) : 0;
	}

	return ret;
}