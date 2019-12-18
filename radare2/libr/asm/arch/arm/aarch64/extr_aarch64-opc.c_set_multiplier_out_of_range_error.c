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
typedef  int /*<<< orphan*/  aarch64_operand_error ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  set_out_of_range_error (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_multiplier_out_of_range_error (aarch64_operand_error *mismatch_detail,
				   int idx, int lower_bound, int upper_bound)
{
  if (mismatch_detail == NULL)
    return;
  set_out_of_range_error (mismatch_detail, idx, lower_bound, upper_bound,
			  _("multiplier"));
}