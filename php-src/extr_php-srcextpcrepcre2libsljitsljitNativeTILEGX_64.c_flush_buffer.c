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
struct sljit_compiler {int dummy; } ;
typedef  int /*<<< orphan*/  sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 scalar_t__ inst_buf_index ; 
 int /*<<< orphan*/  update_buffer (struct sljit_compiler*) ; 

__attribute__((used)) static sljit_s32 flush_buffer(struct sljit_compiler *compiler)
{
	while (inst_buf_index != 0) {
		FAIL_IF(update_buffer(compiler));
	}
	return SLJIT_SUCCESS;
}