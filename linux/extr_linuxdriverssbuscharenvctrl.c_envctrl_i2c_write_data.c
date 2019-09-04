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

/* Variables and functions */
 scalar_t__ PCF8584_DATA ; 
 int /*<<< orphan*/  envtrl_i2c_test_pin () ; 
 scalar_t__ i2c ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 

__attribute__((used)) static void envctrl_i2c_write_data(unsigned char port)
{
	envtrl_i2c_test_pin();
	writeb(port, i2c + PCF8584_DATA);
}