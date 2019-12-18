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
typedef  int /*<<< orphan*/  u8 ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb750_nand_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 rb750_nand_read_byte(struct mtd_info *mtd)
{
	u8 data = 0;
	rb750_nand_read(&data, 1);
	return data;
}