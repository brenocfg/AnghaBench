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
typedef  int /*<<< orphan*/  u16 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int S626_CRBMSK_INTCTRL ; 
 int S626_CRBMSK_LATCHSRC ; 
 int /*<<< orphan*/  S626_LP_CRB (unsigned int) ; 
 int /*<<< orphan*/  S626_SET_CRB_LATCHSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_debi_replace (struct comedi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_set_latch_source(struct comedi_device *dev,
				  unsigned int chan, u16 value)
{
	s626_debi_replace(dev, S626_LP_CRB(chan),
			  ~(S626_CRBMSK_INTCTRL | S626_CRBMSK_LATCHSRC),
			  S626_SET_CRB_LATCHSRC(value));
}