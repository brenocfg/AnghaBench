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
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 

int cadillac_get_torque_idx(int addr, int array_size) {
  return MIN(MAX(addr - 0x151, 0), array_size);  // 0x151 is id 0, 0x152 is id 1 and so on...
}