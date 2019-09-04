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
struct matroxfb_dh_maven_info {int /*<<< orphan*/  ddc2; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_bit_bus_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void i2c_ddc2_done(struct matroxfb_dh_maven_info* minfo2) {
	i2c_bit_bus_del(&minfo2->ddc2);
}