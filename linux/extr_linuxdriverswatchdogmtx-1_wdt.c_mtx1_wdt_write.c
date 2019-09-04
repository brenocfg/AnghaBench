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
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  mtx1_wdt_reset () ; 

__attribute__((used)) static ssize_t mtx1_wdt_write(struct file *file, const char *buf,
						size_t count, loff_t *ppos)
{
	if (!count)
		return -EIO;
	mtx1_wdt_reset();
	return count;
}