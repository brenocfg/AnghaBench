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
 struct comedi_device** comedi_board_minor_table ; 
 int /*<<< orphan*/  comedi_board_minor_table_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct comedi_device *comedi_clear_board_minor(unsigned int minor)
{
	struct comedi_device *dev;

	mutex_lock(&comedi_board_minor_table_lock);
	dev = comedi_board_minor_table[minor];
	comedi_board_minor_table[minor] = NULL;
	mutex_unlock(&comedi_board_minor_table_lock);
	return dev;
}