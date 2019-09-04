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
struct maven_data {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  maven_set_reg (struct i2c_client*,int,int) ; 

__attribute__((used)) static inline int maven_resync(struct maven_data* md) {
	struct i2c_client *c = md->client;
	maven_set_reg(c, 0x95, 0x20);	/* start whole thing */
	return 0;
}