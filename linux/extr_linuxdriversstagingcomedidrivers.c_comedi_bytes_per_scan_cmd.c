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
struct comedi_subdevice {int type; } ;
struct comedi_cmd {unsigned int scan_end_arg; } ;

/* Variables and functions */
#define  COMEDI_SUBD_DI 130 
#define  COMEDI_SUBD_DIO 129 
#define  COMEDI_SUBD_DO 128 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int comedi_bytes_per_sample (struct comedi_subdevice*) ; 
 unsigned int comedi_samples_to_bytes (struct comedi_subdevice*,unsigned int) ; 

unsigned int comedi_bytes_per_scan_cmd(struct comedi_subdevice *s,
				       struct comedi_cmd *cmd)
{
	unsigned int num_samples;
	unsigned int bits_per_sample;

	switch (s->type) {
	case COMEDI_SUBD_DI:
	case COMEDI_SUBD_DO:
	case COMEDI_SUBD_DIO:
		bits_per_sample = 8 * comedi_bytes_per_sample(s);
		num_samples = DIV_ROUND_UP(cmd->scan_end_arg, bits_per_sample);
		break;
	default:
		num_samples = cmd->scan_end_arg;
		break;
	}
	return comedi_samples_to_bytes(s, num_samples);
}