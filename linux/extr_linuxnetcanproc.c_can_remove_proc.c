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
struct TYPE_2__ {scalar_t__ proc_dir; scalar_t__ pde_rcvlist_sff; scalar_t__ pde_rcvlist_eff; scalar_t__ pde_rcvlist_inv; scalar_t__ pde_rcvlist_fil; scalar_t__ pde_rcvlist_all; scalar_t__ pde_rcvlist_err; scalar_t__ pde_reset_stats; scalar_t__ pde_stats; scalar_t__ pde_version; } ;
struct net {scalar_t__ proc_net; TYPE_1__ can; } ;

/* Variables and functions */
 char* CAN_PROC_RCVLIST_ALL ; 
 char* CAN_PROC_RCVLIST_EFF ; 
 char* CAN_PROC_RCVLIST_ERR ; 
 char* CAN_PROC_RCVLIST_FIL ; 
 char* CAN_PROC_RCVLIST_INV ; 
 char* CAN_PROC_RCVLIST_SFF ; 
 char* CAN_PROC_RESET_STATS ; 
 char* CAN_PROC_STATS ; 
 char* CAN_PROC_VERSION ; 
 int /*<<< orphan*/  remove_proc_entry (char*,scalar_t__) ; 

void can_remove_proc(struct net *net)
{
	if (net->can.pde_version)
		remove_proc_entry(CAN_PROC_VERSION, net->can.proc_dir);

	if (net->can.pde_stats)
		remove_proc_entry(CAN_PROC_STATS, net->can.proc_dir);

	if (net->can.pde_reset_stats)
		remove_proc_entry(CAN_PROC_RESET_STATS, net->can.proc_dir);

	if (net->can.pde_rcvlist_err)
		remove_proc_entry(CAN_PROC_RCVLIST_ERR, net->can.proc_dir);

	if (net->can.pde_rcvlist_all)
		remove_proc_entry(CAN_PROC_RCVLIST_ALL, net->can.proc_dir);

	if (net->can.pde_rcvlist_fil)
		remove_proc_entry(CAN_PROC_RCVLIST_FIL, net->can.proc_dir);

	if (net->can.pde_rcvlist_inv)
		remove_proc_entry(CAN_PROC_RCVLIST_INV, net->can.proc_dir);

	if (net->can.pde_rcvlist_eff)
		remove_proc_entry(CAN_PROC_RCVLIST_EFF, net->can.proc_dir);

	if (net->can.pde_rcvlist_sff)
		remove_proc_entry(CAN_PROC_RCVLIST_SFF, net->can.proc_dir);

	if (net->can.proc_dir)
		remove_proc_entry("can", net->proc_net);
}