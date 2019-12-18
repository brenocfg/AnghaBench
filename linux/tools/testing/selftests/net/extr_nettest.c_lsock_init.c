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
struct sock_args {scalar_t__ type; scalar_t__ bind_test_only; int /*<<< orphan*/  version; int /*<<< orphan*/  ifindex; scalar_t__ use_setsockopt; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 long FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 long O_NONBLOCK ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ bind_socket (int,struct sock_args*) ; 
 scalar_t__ bind_to_device (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 long fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 scalar_t__ set_reuseaddr (int) ; 
 scalar_t__ set_reuseport (int) ; 
 scalar_t__ set_unicast_if (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsock_init(struct sock_args *args)
{
	long flags;
	int sd;

	sd = socket(args->version, args->type, args->protocol);
	if (sd < 0) {
		log_err_errno("Error opening socket");
		return  -1;
	}

	if (set_reuseaddr(sd) != 0)
		goto err;

	if (set_reuseport(sd) != 0)
		goto err;

	if (args->dev && bind_to_device(sd, args->dev) != 0)
		goto err;
	else if (args->use_setsockopt &&
		 set_unicast_if(sd, args->ifindex, args->version))
		goto err;

	if (bind_socket(sd, args))
		goto err;

	if (args->bind_test_only)
		goto out;

	if (args->type == SOCK_STREAM && listen(sd, 1) < 0) {
		log_err_errno("listen failed");
		goto err;
	}

	flags = fcntl(sd, F_GETFL);
	if ((flags < 0) || (fcntl(sd, F_SETFL, flags|O_NONBLOCK) < 0)) {
		log_err_errno("Failed to set non-blocking option");
		goto err;
	}

	if (fcntl(sd, F_SETFD, FD_CLOEXEC) < 0)
		log_err_errno("Failed to set close-on-exec flag");

out:
	return sd;

err:
	close(sd);
	return -1;
}