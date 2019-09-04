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
struct s6e63m0 {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short const**) ; 
 int s6e63m0_panel_send_sequence (struct s6e63m0*,unsigned short const*) ; 
 unsigned short const* seq_display_on ; 
 unsigned short const* seq_stand_by_off ; 

__attribute__((used)) static int s6e63m0_ldi_enable(struct s6e63m0 *lcd)
{
	int ret = 0, i;
	const unsigned short *enable_seq[] = {
		seq_stand_by_off,
		seq_display_on,
	};

	for (i = 0; i < ARRAY_SIZE(enable_seq); i++) {
		ret = s6e63m0_panel_send_sequence(lcd, enable_seq[i]);
		if (ret)
			break;
	}

	return ret;
}