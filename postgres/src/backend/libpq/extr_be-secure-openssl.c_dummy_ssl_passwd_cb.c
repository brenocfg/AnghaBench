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
 int /*<<< orphan*/  Assert (int) ; 
 int dummy_ssl_passwd_cb_called ; 

__attribute__((used)) static int
dummy_ssl_passwd_cb(char *buf, int size, int rwflag, void *userdata)
{
	/* Set flag to change the error message we'll report */
	dummy_ssl_passwd_cb_called = true;
	/* And return empty string */
	Assert(size > 0);
	buf[0] = '\0';
	return 0;
}