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
struct most_channel_config {unsigned int subbuffer_size; int data_type; int packets_per_xact; } ;

/* Variables and functions */
 unsigned int AV_PACKETS_PER_XACT ; 
#define  MOST_CH_ISOC 129 
#define  MOST_CH_SYNC 128 
 unsigned int USB_MTU ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static unsigned int get_stream_frame_size(struct most_channel_config *cfg)
{
	unsigned int frame_size = 0;
	unsigned int sub_size = cfg->subbuffer_size;

	if (!sub_size) {
		pr_warn("Misconfig: Subbuffer size zero.\n");
		return frame_size;
	}
	switch (cfg->data_type) {
	case MOST_CH_ISOC:
		frame_size = AV_PACKETS_PER_XACT * sub_size;
		break;
	case MOST_CH_SYNC:
		if (cfg->packets_per_xact == 0) {
			pr_warn("Misconfig: Packets per XACT zero\n");
			frame_size = 0;
		} else if (cfg->packets_per_xact == 0xFF) {
			frame_size = (USB_MTU / sub_size) * sub_size;
		} else {
			frame_size = cfg->packets_per_xact * sub_size;
		}
		break;
	default:
		pr_warn("Query frame size of non-streaming channel\n");
		break;
	}
	return frame_size;
}