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
typedef  int /*<<< orphan*/  grub_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_time_ms_func () ; 

grub_uint64_t
grub_get_time_ms (void)
{
  return get_time_ms_func ();
}