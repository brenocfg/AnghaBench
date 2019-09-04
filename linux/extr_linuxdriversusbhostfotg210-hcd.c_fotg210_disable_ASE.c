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
struct fotg210_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASE ; 
 int /*<<< orphan*/  fotg210_clear_command_bit (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fotg210_disable_ASE(struct fotg210_hcd *fotg210)
{
	fotg210_clear_command_bit(fotg210, CMD_ASE);
}