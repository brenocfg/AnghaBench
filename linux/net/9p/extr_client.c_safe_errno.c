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
 int EPROTO ; 
 int MAX_ERRNO ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int safe_errno(int err)
{
	if ((err > 0) || (err < -MAX_ERRNO)) {
		p9_debug(P9_DEBUG_ERROR, "Invalid error code %d\n", err);
		return -EPROTO;
	}
	return err;
}