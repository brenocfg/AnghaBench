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
struct velocity_opt {int rx_thresh; int DMA_length; int numrx; int numtx; int flow_cntl; int wol_opts; int /*<<< orphan*/  spd_dpx; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_LENGTH_DEF ; 
 int /*<<< orphan*/  DMA_LENGTH_MAX ; 
 int /*<<< orphan*/  DMA_LENGTH_MIN ; 
 int /*<<< orphan*/ * DMA_length ; 
 int /*<<< orphan*/  FLOW_CNTL_DEF ; 
 int /*<<< orphan*/  FLOW_CNTL_MAX ; 
 int /*<<< orphan*/  FLOW_CNTL_MIN ; 
 int /*<<< orphan*/  IP_ALIG_DEF ; 
 int /*<<< orphan*/ * IP_byte_align ; 
 int /*<<< orphan*/  MED_LNK_DEF ; 
 int /*<<< orphan*/  MED_LNK_MAX ; 
 int /*<<< orphan*/  MED_LNK_MIN ; 
 int /*<<< orphan*/  RX_DESC_DEF ; 
 int /*<<< orphan*/  RX_DESC_MAX ; 
 int /*<<< orphan*/  RX_DESC_MIN ; 
 int /*<<< orphan*/  RX_THRESH_DEF ; 
 int /*<<< orphan*/  RX_THRESH_MAX ; 
 int /*<<< orphan*/  RX_THRESH_MIN ; 
 int /*<<< orphan*/ * RxDescriptors ; 
 int /*<<< orphan*/  TX_DESC_DEF ; 
 int /*<<< orphan*/  TX_DESC_MAX ; 
 int /*<<< orphan*/  TX_DESC_MIN ; 
 int /*<<< orphan*/ * TxDescriptors ; 
 int /*<<< orphan*/  VELOCITY_FLAGS_IP_ALIGN ; 
 int /*<<< orphan*/  WOL_OPT_DEF ; 
 int /*<<< orphan*/  WOL_OPT_MAX ; 
 int /*<<< orphan*/  WOL_OPT_MIN ; 
 int /*<<< orphan*/ * flow_control ; 
 int /*<<< orphan*/ * rx_thresh ; 
 int /*<<< orphan*/ * speed_duplex ; 
 int /*<<< orphan*/  velocity_set_bool_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  velocity_set_int_opt (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * wol_opts ; 

__attribute__((used)) static void velocity_get_options(struct velocity_opt *opts, int index,
				 const char *devname)
{

	velocity_set_int_opt(&opts->rx_thresh, rx_thresh[index], RX_THRESH_MIN, RX_THRESH_MAX, RX_THRESH_DEF, "rx_thresh", devname);
	velocity_set_int_opt(&opts->DMA_length, DMA_length[index], DMA_LENGTH_MIN, DMA_LENGTH_MAX, DMA_LENGTH_DEF, "DMA_length", devname);
	velocity_set_int_opt(&opts->numrx, RxDescriptors[index], RX_DESC_MIN, RX_DESC_MAX, RX_DESC_DEF, "RxDescriptors", devname);
	velocity_set_int_opt(&opts->numtx, TxDescriptors[index], TX_DESC_MIN, TX_DESC_MAX, TX_DESC_DEF, "TxDescriptors", devname);

	velocity_set_int_opt(&opts->flow_cntl, flow_control[index], FLOW_CNTL_MIN, FLOW_CNTL_MAX, FLOW_CNTL_DEF, "flow_control", devname);
	velocity_set_bool_opt(&opts->flags, IP_byte_align[index], IP_ALIG_DEF, VELOCITY_FLAGS_IP_ALIGN, "IP_byte_align", devname);
	velocity_set_int_opt((int *) &opts->spd_dpx, speed_duplex[index], MED_LNK_MIN, MED_LNK_MAX, MED_LNK_DEF, "Media link mode", devname);
	velocity_set_int_opt(&opts->wol_opts, wol_opts[index], WOL_OPT_MIN, WOL_OPT_MAX, WOL_OPT_DEF, "Wake On Lan options", devname);
	opts->numrx = (opts->numrx & ~3);
}