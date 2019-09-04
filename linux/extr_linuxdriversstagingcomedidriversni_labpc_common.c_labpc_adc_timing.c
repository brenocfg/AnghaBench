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
struct comedi_device {struct comedi_8254* pacer; } ;
struct comedi_cmd {int flags; } ;
struct comedi_8254 {unsigned int next_div1; unsigned int osc_base; unsigned int next_div; unsigned int next_div2; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 void* DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 void* DIV_ROUND_UP (unsigned int,unsigned int) ; 
 unsigned int I8254_MAX_COUNT ; 
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (struct comedi_8254*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_check_trigger_arg_max (unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  comedi_check_trigger_arg_min (unsigned int*,int) ; 
 unsigned int labpc_ai_convert_period (struct comedi_cmd*,int) ; 
 unsigned int labpc_ai_scan_period (struct comedi_cmd*,int) ; 
 int /*<<< orphan*/  labpc_set_ai_convert_period (struct comedi_cmd*,int,unsigned int) ; 
 int /*<<< orphan*/  labpc_set_ai_scan_period (struct comedi_cmd*,int,unsigned int) ; 

__attribute__((used)) static void labpc_adc_timing(struct comedi_device *dev, struct comedi_cmd *cmd,
			     enum scan_mode mode)
{
	struct comedi_8254 *pacer = dev->pacer;
	unsigned int convert_period = labpc_ai_convert_period(cmd, mode);
	unsigned int scan_period = labpc_ai_scan_period(cmd, mode);
	unsigned int base_period;

	/*
	 * If both convert and scan triggers are TRIG_TIMER, then they
	 * both rely on counter b0. If only one TRIG_TIMER is used, we
	 * can use the generic cascaded timing functions.
	 */
	if (convert_period && scan_period) {
		/*
		 * pick the lowest divisor value we can (for maximum input
		 * clock speed on convert and scan counters)
		 */
		pacer->next_div1 = (scan_period - 1) /
				   (pacer->osc_base * I8254_MAX_COUNT) + 1;

		comedi_check_trigger_arg_min(&pacer->next_div1, 2);
		comedi_check_trigger_arg_max(&pacer->next_div1,
					     I8254_MAX_COUNT);

		base_period = pacer->osc_base * pacer->next_div1;

		/*  set a0 for conversion frequency and b1 for scan frequency */
		switch (cmd->flags & CMDF_ROUND_MASK) {
		default:
		case CMDF_ROUND_NEAREST:
			pacer->next_div = DIV_ROUND_CLOSEST(convert_period,
							    base_period);
			pacer->next_div2 = DIV_ROUND_CLOSEST(scan_period,
							     base_period);
			break;
		case CMDF_ROUND_UP:
			pacer->next_div = DIV_ROUND_UP(convert_period,
						       base_period);
			pacer->next_div2 = DIV_ROUND_UP(scan_period,
							base_period);
			break;
		case CMDF_ROUND_DOWN:
			pacer->next_div = convert_period / base_period;
			pacer->next_div2 = scan_period / base_period;
			break;
		}
		/*  make sure a0 and b1 values are acceptable */
		comedi_check_trigger_arg_min(&pacer->next_div, 2);
		comedi_check_trigger_arg_max(&pacer->next_div, I8254_MAX_COUNT);
		comedi_check_trigger_arg_min(&pacer->next_div2, 2);
		comedi_check_trigger_arg_max(&pacer->next_div2,
					     I8254_MAX_COUNT);

		/*  write corrected timings to command */
		labpc_set_ai_convert_period(cmd, mode,
					    base_period * pacer->next_div);
		labpc_set_ai_scan_period(cmd, mode,
					 base_period * pacer->next_div2);
	} else if (scan_period) {
		/*
		 * calculate cascaded counter values
		 * that give desired scan timing
		 * (pacer->next_div2 / pacer->next_div1)
		 */
		comedi_8254_cascade_ns_to_timer(pacer, &scan_period,
						cmd->flags);
		labpc_set_ai_scan_period(cmd, mode, scan_period);
	} else if (convert_period) {
		/*
		 * calculate cascaded counter values
		 * that give desired conversion timing
		 * (pacer->next_div / pacer->next_div1)
		 */
		comedi_8254_cascade_ns_to_timer(pacer, &convert_period,
						cmd->flags);
		/* transfer div2 value so correct timer gets updated */
		pacer->next_div = pacer->next_div2;
		labpc_set_ai_convert_period(cmd, mode, convert_period);
	}
}