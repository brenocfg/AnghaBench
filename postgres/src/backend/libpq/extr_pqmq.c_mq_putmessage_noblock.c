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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mq_putmessage_noblock(char msgtype, const char *s, size_t len)
{
	/*
	 * While the shm_mq machinery does support sending a message in
	 * non-blocking mode, there's currently no way to try sending beginning to
	 * send the message that doesn't also commit us to completing the
	 * transmission.  This could be improved in the future, but for now we
	 * don't need it.
	 */
	elog(ERROR, "not currently supported");
}