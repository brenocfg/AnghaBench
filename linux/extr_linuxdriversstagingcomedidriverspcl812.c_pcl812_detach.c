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
 int /*<<< orphan*/  comedi_legacy_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl812_free_dma (struct comedi_device*) ; 

__attribute__((used)) static void pcl812_detach(struct comedi_device *dev)
{
	pcl812_free_dma(dev);
	comedi_legacy_detach(dev);
}