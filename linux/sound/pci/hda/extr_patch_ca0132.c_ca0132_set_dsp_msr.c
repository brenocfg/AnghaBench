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
 int /*<<< orphan*/  CONTROL_FLAG_ADC_B_96KHZ ; 
 int /*<<< orphan*/  CONTROL_FLAG_ADC_C_96KHZ ; 
 int /*<<< orphan*/  CONTROL_FLAG_DAC_96KHZ ; 
 int /*<<< orphan*/  CONTROL_FLAG_DSP_96KHZ ; 
 int /*<<< orphan*/  CONTROL_FLAG_SRC_CLOCK_196MHZ ; 
 int /*<<< orphan*/  CONTROL_FLAG_SRC_RATE_96KHZ ; 
 int /*<<< orphan*/  MEM_CONNID_MICIN1 ; 
 int /*<<< orphan*/  MEM_CONNID_MICOUT1 ; 
 int /*<<< orphan*/  MEM_CONNID_WUH ; 
 int /*<<< orphan*/  SR_48_000 ; 
 int /*<<< orphan*/  SR_96_000 ; 
 int /*<<< orphan*/  chipio_set_conn_rate (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipio_set_control_flag (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ca0132_set_dsp_msr(struct hda_codec *codec, bool is96k)
{
	chipio_set_control_flag(codec, CONTROL_FLAG_DSP_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_DAC_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_SRC_RATE_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_SRC_CLOCK_196MHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_ADC_B_96KHZ, is96k);
	chipio_set_control_flag(codec, CONTROL_FLAG_ADC_C_96KHZ, is96k);

	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);
}