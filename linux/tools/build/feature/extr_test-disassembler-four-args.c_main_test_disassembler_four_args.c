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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_big_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_arch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_mach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_openr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disassembler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int main(void)
{
	bfd *abfd = bfd_openr(NULL, NULL);

	disassembler(bfd_get_arch(abfd),
		     bfd_big_endian(abfd),
		     bfd_get_mach(abfd),
		     abfd);

	return 0;
}