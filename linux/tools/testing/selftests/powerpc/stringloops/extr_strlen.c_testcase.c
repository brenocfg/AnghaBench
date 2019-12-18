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
 unsigned long ITERATIONS ; 
 unsigned long SIZE ; 
 int /*<<< orphan*/  bench_test (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* memalign (int,unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int random () ; 
 int /*<<< orphan*/  srandom (int) ; 
 int /*<<< orphan*/  test_one (char*) ; 

__attribute__((used)) static int testcase(void)
{
	char *s;
	unsigned long i;

	s = memalign(128, SIZE);
	if (!s) {
		perror("memalign");
		exit(1);
	}

	srandom(1);

	memset(s, 0, SIZE);
	for (i = 0; i < SIZE; i++) {
		char c;

		do {
			c = random() & 0x7f;
		} while (!c);
		s[i] = c;
		test_one(s);
	}

	for (i = 0; i < ITERATIONS; i++) {
		unsigned long j;

		for (j = 0; j < SIZE; j++) {
			char c;

			do {
				c = random() & 0x7f;
			} while (!c);
			s[j] = c;
		}
		for (j = 0; j < sizeof(long); j++) {
			s[SIZE - 1 - j] = 0;
			test_one(s);
		}
	}

	for (i = 0; i < SIZE; i++) {
		char c;

		do {
			c = random() & 0x7f;
		} while (!c);
		s[i] = c;
	}

	bench_test(s);

	s[16] = 0;
	bench_test(s);

	s[8] = 0;
	bench_test(s);

	s[4] = 0;
	bench_test(s);

	s[3] = 0;
	bench_test(s);

	s[2] = 0;
	bench_test(s);

	s[1] = 0;
	bench_test(s);

	return 0;
}