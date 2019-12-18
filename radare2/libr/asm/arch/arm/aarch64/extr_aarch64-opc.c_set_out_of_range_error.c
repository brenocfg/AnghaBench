#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* data; } ;
typedef  TYPE_1__ aarch64_operand_error ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_OPDE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  set_error (TYPE_1__*,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static inline void
set_out_of_range_error (aarch64_operand_error *mismatch_detail,
			int idx, int lower_bound, int upper_bound,
			const char* error)
{
  if (mismatch_detail == NULL)
    return;
  set_error (mismatch_detail, AARCH64_OPDE_OUT_OF_RANGE, idx, error);
  mismatch_detail->data[0] = lower_bound;
  mismatch_detail->data[1] = upper_bound;
}