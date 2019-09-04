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
 int /*<<< orphan*/  DT_C_READ_ADIM ; 
 int dt2801_readdata2 (struct comedi_device*,int*) ; 
 int /*<<< orphan*/  dt2801_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  dt2801_writecmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt2801_writedata (struct comedi_device*,int) ; 

__attribute__((used)) static int probe_number_of_ai_chans(struct comedi_device *dev)
{
	int n_chans;
	int stat;
	int data;

	for (n_chans = 0; n_chans < 16; n_chans++) {
		dt2801_writecmd(dev, DT_C_READ_ADIM);
		dt2801_writedata(dev, 0);
		dt2801_writedata(dev, n_chans);
		stat = dt2801_readdata2(dev, &data);

		if (stat)
			break;
	}

	dt2801_reset(dev);
	dt2801_reset(dev);

	return n_chans;
}