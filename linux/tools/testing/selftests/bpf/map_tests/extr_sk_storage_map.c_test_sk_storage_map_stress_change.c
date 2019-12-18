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
 int /*<<< orphan*/  CHECK (int,char*,char*,int) ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  alarm (scalar_t__) ; 
 int do_sk_storage_map_stress_change () ; 
 scalar_t__ runtime_s ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_handler ; 

__attribute__((used)) static void test_sk_storage_map_stress_change(void)
{
	int err;

	signal(SIGTERM, stop_handler);
	signal(SIGINT, stop_handler);
	if (runtime_s > 0) {
		signal(SIGALRM, stop_handler);
		alarm(runtime_s);
	}

	err = do_sk_storage_map_stress_change();

	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (runtime_s > 0) {
		signal(SIGALRM, SIG_DFL);
		alarm(0);
	}

	CHECK(err, "test_sk_storage_map_stress_change", "err:%d\n", err);
}