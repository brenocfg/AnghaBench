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
 int /*<<< orphan*/  OBD_SEND_STOP ; 
 scalar_t__ PCF8584_CSR ; 
 int /*<<< orphan*/  envtrl_i2c_test_pin () ; 
 scalar_t__ i2c ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void envctrl_i2c_stop(void)
{
	envtrl_i2c_test_pin();
	writeb(OBD_SEND_STOP, i2c + PCF8584_CSR);
}