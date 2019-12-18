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
 scalar_t__ EFBIG ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int errcode (int /*<<< orphan*/ ) ; 
 int errcode_for_file_access () ; 
 scalar_t__ errno ; 

__attribute__((used)) static int
errcode_for_dynamic_shared_memory(void)
{
	if (errno == EFBIG || errno == ENOMEM)
		return errcode(ERRCODE_OUT_OF_MEMORY);
	else
		return errcode_for_file_access();
}