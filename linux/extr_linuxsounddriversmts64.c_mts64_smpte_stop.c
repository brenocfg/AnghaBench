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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS64_CMD_SMPTE_STOP ; 
 int /*<<< orphan*/  mts64_write_command (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mts64_smpte_stop(struct parport *p)
{
	mts64_write_command(p, MTS64_CMD_SMPTE_STOP);
}