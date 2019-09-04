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
struct comedi_8254 {int dummy; } ;

/* Variables and functions */
 unsigned int I8254_CTRL_READBACK_SEL_CTR (unsigned int) ; 
 unsigned int I8254_CTRL_READBACK_STATUS ; 
 int /*<<< orphan*/  I8254_CTRL_REG ; 
 unsigned int __i8254_read (struct comedi_8254*,unsigned int) ; 
 int /*<<< orphan*/  __i8254_write (struct comedi_8254*,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int comedi_8254_status(struct comedi_8254 *i8254, unsigned int counter)
{
	unsigned int cmd;

	if (counter > 2)
		return 0;

	cmd = I8254_CTRL_READBACK_STATUS | I8254_CTRL_READBACK_SEL_CTR(counter);
	__i8254_write(i8254, cmd, I8254_CTRL_REG);

	return __i8254_read(i8254, counter);
}