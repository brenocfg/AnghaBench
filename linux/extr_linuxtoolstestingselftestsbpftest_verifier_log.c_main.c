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
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOSPC ; 
 int LOG_SIZE ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  test_log_bad (char*,int,int) ; 
 int /*<<< orphan*/  test_log_good (char*,int,size_t,size_t,int /*<<< orphan*/ ,char*) ; 

int main(int argc, char **argv)
{
	char full_log[LOG_SIZE];
	char log[LOG_SIZE];
	size_t want_len;
	int i;

	memset(log, 1, LOG_SIZE);

	/* Test incorrect attr */
	printf("Test log_level 0...\n");
	test_log_bad(log, LOG_SIZE, 0);

	printf("Test log_size < 128...\n");
	test_log_bad(log, 15, 1);

	printf("Test log_buff = NULL...\n");
	test_log_bad(NULL, LOG_SIZE, 1);

	/* Test with log big enough */
	printf("Test oversized buffer...\n");
	test_log_good(full_log, LOG_SIZE, LOG_SIZE, 0, EACCES, full_log);

	want_len = strlen(full_log);

	printf("Test exact buffer...\n");
	test_log_good(log, LOG_SIZE, want_len + 2, want_len, EACCES, full_log);

	printf("Test undersized buffers...\n");
	for (i = 0; i < 64; i++) {
		full_log[want_len - i + 1] = 1;
		full_log[want_len - i] = 0;

		test_log_good(log, LOG_SIZE, want_len + 1 - i, want_len - i,
			      ENOSPC, full_log);
	}

	printf("test_verifier_log: OK\n");
	return 0;
}