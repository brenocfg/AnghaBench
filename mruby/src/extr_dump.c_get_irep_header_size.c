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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */

__attribute__((used)) static size_t
get_irep_header_size(mrb_state *mrb)
{
  size_t size = 0;

  size += sizeof(uint32_t) * 1;
  size += sizeof(uint16_t) * 3;

  return size;
}