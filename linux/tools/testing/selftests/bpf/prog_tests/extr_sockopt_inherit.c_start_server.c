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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int CUSTOM_INHERIT1 ; 
 int CUSTOM_LISTENER ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_CUSTOM ; 
 scalar_t__ bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_server(void)
{
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK),
	};
	char buf;
	int err;
	int fd;
	int i;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		log_err("Failed to create server socket");
		return -1;
	}

	for (i = CUSTOM_INHERIT1; i <= CUSTOM_LISTENER; i++) {
		buf = 0x01;
		err = setsockopt(fd, SOL_CUSTOM, i, &buf, 1);
		if (err) {
			log_err("Failed to call setsockopt(%d)", i);
			close(fd);
			return -1;
		}
	}

	if (bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
		log_err("Failed to bind socket");
		close(fd);
		return -1;
	}

	return fd;
}