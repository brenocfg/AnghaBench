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
typedef  int /*<<< orphan*/  u32 ;
struct sas_identify_frame {int dummy; } ;
struct mvs_info {int id; TYPE_1__* chip; } ;
struct TYPE_2__ {int n_phy; } ;

/* Variables and functions */
 scalar_t__ CONFIG_ATT_ID_FRAME0 ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sas_identify_frame*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mv_dprintk (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_read_port_cfg_data (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_write_port_cfg_addr (struct mvs_info*,int,scalar_t__) ; 

__attribute__((used)) static void mvs_94xx_get_att_identify_frame(struct mvs_info *mvi, int port_id,
					struct sas_identify_frame *id)
{
	int i;
	u32 id_frame[7];

	for (i = 0; i < 7; i++) {
		mvs_write_port_cfg_addr(mvi, port_id,
					CONFIG_ATT_ID_FRAME0 + i * 4);
		id_frame[i] = cpu_to_le32(mvs_read_port_cfg_data(mvi, port_id));
		mv_dprintk("94xx phy %d atta frame %d %x.\n",
			port_id + mvi->id * mvi->chip->n_phy, i, id_frame[i]);
	}
	memcpy(id, id_frame, 28);
}