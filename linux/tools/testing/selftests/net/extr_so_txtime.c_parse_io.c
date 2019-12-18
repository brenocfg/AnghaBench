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
struct timed_send {int delay_us; char data; } ;

/* Variables and functions */
 int MAX_NUM_PKT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_io(const char *optarg, struct timed_send *array)
{
	char *arg, *tok;
	int aoff = 0;

	arg = strdup(optarg);
	if (!arg)
		error(1, errno, "strdup");

	while ((tok = strtok(arg, ","))) {
		arg = NULL;	/* only pass non-zero on first call */

		if (aoff / 2 == MAX_NUM_PKT)
			error(1, 0, "exceeds max pkt count (%d)", MAX_NUM_PKT);

		if (aoff & 1) {	/* parse delay */
			array->delay_us = strtol(tok, NULL, 0) * 1000;
			array++;
		} else {	/* parse character */
			array->data = tok[0];
		}

		aoff++;
	}

	free(arg);

	return aoff / 2;
}