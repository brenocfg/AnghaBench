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
 int /*<<< orphan*/  STATUS (struct parport*) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int parport_pc_read_status (struct parport*) ; 

__attribute__((used)) static int clear_epp_timeout(struct parport *pb)
{
	unsigned char r;

	if (!(parport_pc_read_status(pb) & 0x01))
		return 1;

	/* To clear timeout some chips require double read */
	parport_pc_read_status(pb);
	r = parport_pc_read_status(pb);
	outb(r | 0x01, STATUS(pb)); /* Some reset by writing 1 */
	outb(r & 0xfe, STATUS(pb)); /* Others by writing 0 */
	r = parport_pc_read_status(pb);

	return !(r & 0x01);
}