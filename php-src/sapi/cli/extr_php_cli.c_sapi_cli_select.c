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
struct timeval {long tv_sec; scalar_t__ tv_usec; } ;
typedef  scalar_t__ php_socket_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ FG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_SAFE_FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_socket_timeout ; 
 int php_select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static inline int sapi_cli_select(php_socket_t fd)
{
	fd_set wfd;
	struct timeval tv;
	int ret;

	FD_ZERO(&wfd);

	PHP_SAFE_FD_SET(fd, &wfd);

	tv.tv_sec = (long)FG(default_socket_timeout);
	tv.tv_usec = 0;

	ret = php_select(fd+1, NULL, &wfd, NULL, &tv);

	return ret != -1;
}