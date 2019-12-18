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
 int /*<<< orphan*/  fuzzer_init_php () ; 

int LLVMFuzzerInitialize(int *argc, char ***argv) {
	fuzzer_init_php();

	/* fuzzer_shutdown_php(); */
	return 0;
}