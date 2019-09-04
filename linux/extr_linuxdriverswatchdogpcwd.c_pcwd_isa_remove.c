#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_2__ {int io_addr; scalar_t__ revision; scalar_t__ supports_temp; } ;

/* Variables and functions */
 scalar_t__ DEBUG ; 
 scalar_t__ PCWD_REVISION_A ; 
 int /*<<< orphan*/  cards_found ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pcwd_miscdev ; 
 TYPE_1__ pcwd_private ; 
 int /*<<< orphan*/  pcwd_stop () ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  temp_miscdev ; 

__attribute__((used)) static int pcwd_isa_remove(struct device *dev, unsigned int id)
{
	if (debug >= DEBUG)
		pr_debug("pcwd_isa_remove id=%d\n", id);

	if (!pcwd_private.io_addr)
		return 1;

	/*  Disable the board  */
	if (!nowayout)
		pcwd_stop();

	/* Deregister */
	misc_deregister(&pcwd_miscdev);
	if (pcwd_private.supports_temp)
		misc_deregister(&temp_miscdev);
	release_region(pcwd_private.io_addr,
			(pcwd_private.revision == PCWD_REVISION_A) ? 2 : 4);
	pcwd_private.io_addr = 0x0000;
	cards_found--;

	return 0;
}