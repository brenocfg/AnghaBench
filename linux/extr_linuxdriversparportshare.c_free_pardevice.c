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
struct pardevice {struct pardevice* name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pardevice*) ; 
 struct pardevice* to_pardevice (struct device*) ; 

__attribute__((used)) static void free_pardevice(struct device *dev)
{
	struct pardevice *par_dev = to_pardevice(dev);

	kfree(par_dev->name);
	kfree(par_dev);
}