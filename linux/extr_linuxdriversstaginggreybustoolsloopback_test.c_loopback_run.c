#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct loopback_test {char* test_name; int /*<<< orphan*/  test_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_poll_files (struct loopback_test*) ; 
 TYPE_1__* dict ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  get_results (struct loopback_test*) ; 
 int /*<<< orphan*/  log_results (struct loopback_test*) ; 
 int open_poll_files (struct loopback_test*) ; 
 int /*<<< orphan*/  prepare_devices (struct loopback_test*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  start (struct loopback_test*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int wait_for_complete (struct loopback_test*) ; 

void loopback_run(struct loopback_test *t)
{
	int i;
	int ret;

	for (i = 0; dict[i].name != NULL; i++) {
		if (strstr(dict[i].name, t->test_name))
			t->test_id = dict[i].type;
	}
	if (!t->test_id) {
		fprintf(stderr, "invalid test %s\n", t->test_name);
		usage();
		return;
	}

	prepare_devices(t);

	ret = open_poll_files(t);
	if (ret)
		goto err;

	start(t);

	ret = wait_for_complete(t);
	close_poll_files(t);
	if (ret)
		goto err;


	get_results(t);

	log_results(t);

	return;

err:
	printf("Error running test\n");
	return;
}