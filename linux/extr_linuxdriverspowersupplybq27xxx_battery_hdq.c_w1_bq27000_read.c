#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct w1_slave {TYPE_1__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 unsigned int HDQ_CMD_READ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_read_8 (TYPE_1__*) ; 
 int /*<<< orphan*/  w1_write_8 (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int w1_bq27000_read(struct w1_slave *sl, unsigned int reg)
{
	u8 val;

	mutex_lock(&sl->master->bus_mutex);
	w1_write_8(sl->master, HDQ_CMD_READ | reg);
	val = w1_read_8(sl->master);
	mutex_unlock(&sl->master->bus_mutex);

	return val;
}