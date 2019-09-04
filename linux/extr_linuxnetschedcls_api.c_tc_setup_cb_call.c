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
struct tcf_exts {int dummy; } ;
struct tcf_block {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int tc_exts_setup_cb_egdev_call (struct tcf_exts*,int,void*,int) ; 
 int tcf_block_cb_call (struct tcf_block*,int,void*,int) ; 

int tc_setup_cb_call(struct tcf_block *block, struct tcf_exts *exts,
		     enum tc_setup_type type, void *type_data, bool err_stop)
{
	int ok_count;
	int ret;

	ret = tcf_block_cb_call(block, type, type_data, err_stop);
	if (ret < 0)
		return ret;
	ok_count = ret;

	if (!exts || ok_count)
		return ok_count;
	ret = tc_exts_setup_cb_egdev_call(exts, type, type_data, err_stop);
	if (ret < 0)
		return ret;
	ok_count += ret;

	return ok_count;
}