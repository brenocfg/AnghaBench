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
 scalar_t__ SOCK_STREAM ; 
 int cfg_payload_len ; 
 scalar_t__ cfg_proto ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int saved_tskey ; 
 int saved_tskey_type ; 
 int /*<<< orphan*/  stderr ; 
 int test_failed ; 

__attribute__((used)) static void validate_key(int tskey, int tstype)
{
	int stepsize;

	/* compare key for each subsequent request
	 * must only test for one type, the first one requested
	 */
	if (saved_tskey == -1)
		saved_tskey_type = tstype;
	else if (saved_tskey_type != tstype)
		return;

	stepsize = cfg_proto == SOCK_STREAM ? cfg_payload_len : 1;
	if (tskey != saved_tskey + stepsize) {
		fprintf(stderr, "ERROR: key %d, expected %d\n",
				tskey, saved_tskey + stepsize);
		test_failed = true;
	}

	saved_tskey = tskey;
}