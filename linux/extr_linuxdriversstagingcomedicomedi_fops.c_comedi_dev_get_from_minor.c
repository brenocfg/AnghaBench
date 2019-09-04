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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 struct comedi_device* comedi_dev_get_from_board_minor (unsigned int) ; 
 struct comedi_device* comedi_dev_get_from_subdevice_minor (unsigned int) ; 

struct comedi_device *comedi_dev_get_from_minor(unsigned int minor)
{
	if (minor < COMEDI_NUM_BOARD_MINORS)
		return comedi_dev_get_from_board_minor(minor);

	return comedi_dev_get_from_subdevice_minor(minor);
}