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
 int /*<<< orphan*/  AARCH64_OPDE_OTHER_ERROR ; 
 int /*<<< orphan*/  set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static inline void
set_other_error (aarch64_operand_error *mismatch_detail, int idx,
		 const char* error)
{
  if (mismatch_detail == NULL)
    return;
  set_error (mismatch_detail, AARCH64_OPDE_OTHER_ERROR, idx, error);
}