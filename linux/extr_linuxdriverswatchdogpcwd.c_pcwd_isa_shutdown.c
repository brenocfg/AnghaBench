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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  pcwd_stop () ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static void pcwd_isa_shutdown(struct device *dev, unsigned int id)
{
	if (debug >= DEBUG)
		pr_debug("pcwd_isa_shutdown id=%d\n", id);

	pcwd_stop();
}