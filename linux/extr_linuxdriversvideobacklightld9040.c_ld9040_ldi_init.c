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
struct ld9040 {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short const**) ; 
 int ld9040_panel_send_sequence (struct ld9040*,unsigned short const*) ; 
#define  seq_display_ctrl 136 
#define  seq_elvss_on 135 
#define  seq_gamma_ctrl 134 
#define  seq_gamma_set1 133 
#define  seq_gtcon 132 
#define  seq_manual_pwr 131 
#define  seq_panel_condition 130 
#define  seq_sleep_out 129 
#define  seq_user_setting 128 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ld9040_ldi_init(struct ld9040 *lcd)
{
	int ret, i;
	static const unsigned short *init_seq[] = {
		seq_user_setting,
		seq_panel_condition,
		seq_display_ctrl,
		seq_manual_pwr,
		seq_elvss_on,
		seq_gtcon,
		seq_gamma_set1,
		seq_gamma_ctrl,
		seq_sleep_out,
	};

	for (i = 0; i < ARRAY_SIZE(init_seq); i++) {
		ret = ld9040_panel_send_sequence(lcd, init_seq[i]);
		/* workaround: minimum delay time for transferring CMD */
		usleep_range(300, 310);
		if (ret)
			break;
	}

	return ret;
}