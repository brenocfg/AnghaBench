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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 scalar_t__ get_irep_header_size (int /*<<< orphan*/ *) ; 
 scalar_t__ get_iseq_block_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_pool_block_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_syms_block_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
get_irep_record_size_1(mrb_state *mrb, mrb_irep *irep)
{
  size_t size = 0;

  size += get_irep_header_size(mrb);
  size += get_iseq_block_size(mrb, irep);
  size += get_pool_block_size(mrb, irep);
  size += get_syms_block_size(mrb, irep);
  return size;
}