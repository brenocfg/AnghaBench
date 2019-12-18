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
struct TYPE_2__ {int /*<<< orphan*/  listening_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int errno ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_php_soft_quit () ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sig_soft_quit(int signo) /* {{{ */
{
	int saved_errno = errno;

	/* closing fastcgi listening socket will force fcgi_accept() exit immediately */
	close(fpm_globals.listening_socket);
	if (0 > socket(AF_UNIX, SOCK_STREAM, 0)) {
		zlog(ZLOG_WARNING, "failed to create a new socket");
	}
	fpm_php_soft_quit();
	errno = saved_errno;
}