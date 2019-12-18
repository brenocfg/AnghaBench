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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_PARAM_STREAM_CONTROL ; 
 int /*<<< orphan*/  CONTROL_PARAM_STREAM_ID ; 
 int /*<<< orphan*/  chipio_set_control_param_no_mutex (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chipio_set_stream_control(struct hda_codec *codec,
				int streamid, int enable)
{
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_ID, streamid);
	chipio_set_control_param_no_mutex(codec,
			CONTROL_PARAM_STREAM_CONTROL, enable);
}