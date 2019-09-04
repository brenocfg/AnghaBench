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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  int /*<<< orphan*/  u16 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zd_iowrite16_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int zd_iowrite16(struct zd_chip *chip, zd_addr_t addr, u16 value)
{
	int r;

	mutex_lock(&chip->mutex);
	r = zd_iowrite16_locked(chip, value, addr);
	mutex_unlock(&chip->mutex);
	return r;
}