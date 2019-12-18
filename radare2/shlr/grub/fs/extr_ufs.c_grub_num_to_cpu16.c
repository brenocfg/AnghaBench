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
typedef  int /*<<< orphan*/  grub_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_be_to_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_le_to_cpu16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_uint16_t
grub_num_to_cpu16 (grub_uint16_t num, int be)
{
  return (be) ? grub_be_to_cpu16 (num) : grub_le_to_cpu16 (num);
}