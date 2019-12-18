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
typedef  size_t socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BINDTODEVICE ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 

__attribute__((used)) static int get_bind_to_device(int sd, char *name, size_t len)
{
	int rc;
	socklen_t optlen = len;

	name[0] = '\0';
	rc = getsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, name, &optlen);
	if (rc < 0)
		log_err_errno("setsockopt(SO_BINDTODEVICE)");

	return rc;
}