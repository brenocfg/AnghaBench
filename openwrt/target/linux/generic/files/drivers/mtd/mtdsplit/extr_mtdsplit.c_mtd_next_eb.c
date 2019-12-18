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
struct mtd_info {scalar_t__ erasesize; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ mtd_rounddown_to_eb (size_t,struct mtd_info*) ; 

__attribute__((used)) static ssize_t mtd_next_eb(struct mtd_info *mtd, size_t offset)
{
	return mtd_rounddown_to_eb(offset, mtd) + mtd->erasesize;
}