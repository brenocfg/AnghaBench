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
typedef  int uint ;
typedef  int /*<<< orphan*/  UZLIB_DATA ;

/* Variables and functions */
 int get_uint16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint get_le_uint32 (UZLIB_DATA *d) {
  uint v = get_uint16(d);
  return  v | ((uint) get_uint16(d) << 16);
}