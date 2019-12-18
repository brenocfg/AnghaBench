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
typedef  size_t u16 ;
struct es1968 {size_t* maestro_map; scalar_t__ io_port; } ;

/* Variables and functions */
 scalar_t__ ESM_DATA ; 
 scalar_t__ ESM_INDEX ; 
 int /*<<< orphan*/  outw (size_t,scalar_t__) ; 

__attribute__((used)) static void __maestro_write(struct es1968 *chip, u16 reg, u16 data)
{
	outw(reg, chip->io_port + ESM_INDEX);
	outw(data, chip->io_port + ESM_DATA);
	chip->maestro_map[reg] = data;
}