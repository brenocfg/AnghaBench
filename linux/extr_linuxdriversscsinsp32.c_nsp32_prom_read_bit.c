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
 int nsp32_prom_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_prom_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nsp32_prom_read_bit(nsp32_hw_data *data)
{
	int val;

	/* read */
	nsp32_prom_set(data, ENA, 0);	/* input mode */
	nsp32_prom_set(data, SCL, 1);

	val = nsp32_prom_get(data, SDA);

	nsp32_prom_set(data, SCL, 0);
	nsp32_prom_set(data, ENA, 1);	/* output mode */

	return val;
}