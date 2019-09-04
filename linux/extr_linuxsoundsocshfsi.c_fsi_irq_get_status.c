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
typedef  int /*<<< orphan*/  u32 ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsi_core_read (struct fsi_master*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_st ; 

__attribute__((used)) static u32 fsi_irq_get_status(struct fsi_master *master)
{
	return fsi_core_read(master, int_st);
}