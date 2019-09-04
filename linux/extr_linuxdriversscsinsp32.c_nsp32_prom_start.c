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
typedef  int /*<<< orphan*/  nsp32_hw_data ;

/* Variables and functions */
 int /*<<< orphan*/  ENA ; 
 int /*<<< orphan*/  SCL ; 
 int /*<<< orphan*/  SDA ; 
 int /*<<< orphan*/  nsp32_prom_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nsp32_prom_start (nsp32_hw_data *data)
{
	/* start condition */
	nsp32_prom_set(data, SCL, 1);
	nsp32_prom_set(data, SDA, 1);
	nsp32_prom_set(data, ENA, 1);	/* output mode */
	nsp32_prom_set(data, SDA, 0);	/* keeping SCL=1 and transiting
					 * SDA 1->0 is start condition */
	nsp32_prom_set(data, SCL, 0);
}