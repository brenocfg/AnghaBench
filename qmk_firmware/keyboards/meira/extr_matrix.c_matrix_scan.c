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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  _matrix_scan () ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 

uint8_t matrix_scan(void)
{
	uint8_t ret = _matrix_scan();
	matrix_scan_quantum();
	return ret;
}