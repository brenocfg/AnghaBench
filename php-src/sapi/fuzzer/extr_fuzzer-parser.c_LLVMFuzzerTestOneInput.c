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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  fuzzer_do_request_from_buffer (char*,char*,size_t) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	char *s;
	if (Size > 32 * 1024) {
		/* Large inputs have a large impact on fuzzer performance,
		 * but are unlikely to be necessary to reach new codepaths. */
		return 0;
	}

	s = malloc(Size+1);
	memcpy(s, Data, Size);
	s[Size] = '\0';

	fuzzer_do_request_from_buffer("fuzzer.php", s, Size);

	/* Do not free s: fuzzer_do_request_from_buffer() takes ownership of the allocation. */
	return 0;
}