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
 int /*<<< orphan*/  S626_LP_MISC1 ; 
 int /*<<< orphan*/  S626_LP_WRMISC2 ; 
 int /*<<< orphan*/  S626_MISC1_WDISABLE ; 
 int /*<<< orphan*/  S626_MISC1_WENABLE ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_write_misc2(struct comedi_device *dev, u16 new_image)
{
	s626_debi_write(dev, S626_LP_MISC1, S626_MISC1_WENABLE);
	s626_debi_write(dev, S626_LP_WRMISC2, new_image);
	s626_debi_write(dev, S626_LP_MISC1, S626_MISC1_WDISABLE);
}