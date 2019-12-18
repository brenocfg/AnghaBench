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
struct obs_output {int /*<<< orphan*/  (* delay_callback ) (struct obs_output*,int /*<<< orphan*/ *) ;} ;
struct delay_data {int msg; int /*<<< orphan*/  ts; int /*<<< orphan*/  packet; } ;

/* Variables and functions */
#define  DELAY_MSG_PACKET 130 
#define  DELAY_MSG_START 129 
#define  DELAY_MSG_STOP 128 
 int /*<<< orphan*/  delay_active (struct obs_output*) ; 
 int /*<<< orphan*/  delay_capturing (struct obs_output*) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_output_actual_start (struct obs_output*) ; 
 int /*<<< orphan*/  obs_output_actual_stop (struct obs_output*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct obs_output*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void process_delay_data(struct obs_output *output,
				      struct delay_data *dd)
{
	switch (dd->msg) {
	case DELAY_MSG_PACKET:
		if (!delay_active(output) || !delay_capturing(output))
			obs_encoder_packet_release(&dd->packet);
		else
			output->delay_callback(output, &dd->packet);
		break;
	case DELAY_MSG_START:
		obs_output_actual_start(output);
		break;
	case DELAY_MSG_STOP:
		obs_output_actual_stop(output, false, dd->ts);
		break;
	}
}