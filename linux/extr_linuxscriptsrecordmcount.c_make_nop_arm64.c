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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fd_map ; 
 int /*<<< orphan*/  ideal_nop ; 
 int /*<<< orphan*/  ulseek (int /*<<< orphan*/ ,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int make_nop_arm64(void *map, size_t const offset)
{
	uint32_t *ptr;

	ptr = map + offset;
	/* bl <_mcount> is 0x94000000 before relocation */
	if (*ptr != 0x94000000)
		return -1;

	/* Convert to nop */
	ulseek(fd_map, offset, SEEK_SET);
	uwrite(fd_map, ideal_nop, 4);
	return 0;
}