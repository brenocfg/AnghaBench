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
typedef  int u16 ;
struct es1968 {int* maestro_map; scalar_t__ io_port; } ;

/* Variables and functions */
 scalar_t__ ESM_DATA ; 
 scalar_t__ ESM_INDEX ; 
 int READABLE_MAP ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static u16 __maestro_read(struct es1968 *chip, u16 reg)
{
	if (READABLE_MAP & (1 << reg)) {
		outw(reg, chip->io_port + ESM_INDEX);
		chip->maestro_map[reg] = inw(chip->io_port + ESM_DATA);
	}
	return chip->maestro_map[reg];
}