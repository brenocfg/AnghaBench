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
struct comedi_8254 {int /*<<< orphan*/  divisor1; int /*<<< orphan*/  divisor2; } ;

/* Variables and functions */
 unsigned int I8254_BINARY ; 
 unsigned int I8254_MODE0 ; 
 unsigned int I8254_MODE2 ; 
 int /*<<< orphan*/  comedi_8254_set_mode (struct comedi_8254*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  comedi_8254_write (struct comedi_8254*,unsigned int,int /*<<< orphan*/ ) ; 

void comedi_8254_pacer_enable(struct comedi_8254 *i8254,
			      unsigned int counter1,
			      unsigned int counter2,
			      bool enable)
{
	unsigned int mode;

	if (counter1 > 2 || counter2 > 2 || counter1 == counter2)
		return;

	if (enable)
		mode = I8254_MODE2 | I8254_BINARY;
	else
		mode = I8254_MODE0 | I8254_BINARY;

	comedi_8254_set_mode(i8254, counter1, mode);
	comedi_8254_set_mode(i8254, counter2, mode);

	if (enable) {
		/*
		 * Divisors are loaded second counter then first counter to
		 * avoid possible issues with the first counter expiring
		 * before the second counter is loaded.
		 */
		comedi_8254_write(i8254, counter2, i8254->divisor2);
		comedi_8254_write(i8254, counter1, i8254->divisor1);
	}
}