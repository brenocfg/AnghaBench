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
 int /*<<< orphan*/  db2k_activate_reference_dacs (struct comedi_device*) ; 
 int /*<<< orphan*/  db2k_adc_disarm (struct comedi_device*) ; 
 int /*<<< orphan*/  db2k_initialize_ctrs (struct comedi_device*) ; 
 int /*<<< orphan*/  db2k_initialize_tmrs (struct comedi_device*) ; 

__attribute__((used)) static void db2k_initialize_adc(struct comedi_device *dev)
{
	db2k_adc_disarm(dev);
	db2k_activate_reference_dacs(dev);
	db2k_initialize_ctrs(dev);
	db2k_initialize_tmrs(dev);
}