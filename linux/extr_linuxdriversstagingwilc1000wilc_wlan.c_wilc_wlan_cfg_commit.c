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
typedef  void* u8 ;
typedef  int u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct wilc_cfg_frame {char* wid_header; } ;
struct wilc {int cfg_frame_offset; int cfg_seq_no; struct wilc_cfg_frame cfg_frame; } ;

/* Variables and functions */
 int DRIVER_HANDLER_SIZE ; 
 int WILC_CFG_SET ; 
 int /*<<< orphan*/  wilc_wlan_txq_add_cfg_pkt (struct wilc_vif*,int*,int) ; 

__attribute__((used)) static int wilc_wlan_cfg_commit(struct wilc_vif *vif, int type,
				u32 drv_handler)
{
	struct wilc *wilc = vif->wilc;
	struct wilc_cfg_frame *cfg = &wilc->cfg_frame;
	int total_len = wilc->cfg_frame_offset + 4 + DRIVER_HANDLER_SIZE;
	int seq_no = wilc->cfg_seq_no % 256;
	int driver_handler = (u32)drv_handler;

	if (type == WILC_CFG_SET)
		cfg->wid_header[0] = 'W';
	else
		cfg->wid_header[0] = 'Q';
	cfg->wid_header[1] = seq_no;
	cfg->wid_header[2] = (u8)total_len;
	cfg->wid_header[3] = (u8)(total_len >> 8);
	cfg->wid_header[4] = (u8)driver_handler;
	cfg->wid_header[5] = (u8)(driver_handler >> 8);
	cfg->wid_header[6] = (u8)(driver_handler >> 16);
	cfg->wid_header[7] = (u8)(driver_handler >> 24);
	wilc->cfg_seq_no = seq_no;

	if (!wilc_wlan_txq_add_cfg_pkt(vif, &cfg->wid_header[0], total_len))
		return -1;

	return 0;
}