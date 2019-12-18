#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct p9_fd_opts {int /*<<< orphan*/  wfd; int /*<<< orphan*/  rfd; } ;
struct TYPE_4__ {int /*<<< orphan*/  wfd; int /*<<< orphan*/  rfd; } ;
struct TYPE_3__ {TYPE_2__ fd; } ;
struct p9_client {TYPE_1__ trans_opts; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  p9_conn_create (struct p9_client*) ; 
 int p9_fd_open (struct p9_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_opts (char*,struct p9_fd_opts*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
p9_fd_create(struct p9_client *client, const char *addr, char *args)
{
	int err;
	struct p9_fd_opts opts;

	parse_opts(args, &opts);
	client->trans_opts.fd.rfd = opts.rfd;
	client->trans_opts.fd.wfd = opts.wfd;

	if (opts.rfd == ~0 || opts.wfd == ~0) {
		pr_err("Insufficient options for proto=fd\n");
		return -ENOPROTOOPT;
	}

	err = p9_fd_open(client, opts.rfd, opts.wfd);
	if (err < 0)
		return err;

	p9_conn_create(client);

	return 0;
}