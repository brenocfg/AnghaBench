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
typedef  enum ca0132_sample_rate { ____Placeholder_ca0132_sample_rate } ca0132_sample_rate ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_PARAM_CONN_POINT_ID ; 
 int /*<<< orphan*/  CONTROL_PARAM_CONN_POINT_SAMPLE_RATE ; 
 int /*<<< orphan*/  chipio_set_control_param (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chipio_set_conn_rate(struct hda_codec *codec,
				int connid, enum ca0132_sample_rate rate)
{
	chipio_set_control_param(codec, CONTROL_PARAM_CONN_POINT_ID, connid);
	chipio_set_control_param(codec, CONTROL_PARAM_CONN_POINT_SAMPLE_RATE,
				 rate);
}