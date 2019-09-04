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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSOCK ; 
 struct socket* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct socket*) ; 
 struct socket* get_raw_socket (int) ; 
 struct socket* get_tap_socket (int) ; 

__attribute__((used)) static struct socket *get_socket(int fd)
{
	struct socket *sock;

	/* special case to disable backend */
	if (fd == -1)
		return NULL;
	sock = get_raw_socket(fd);
	if (!IS_ERR(sock))
		return sock;
	sock = get_tap_socket(fd);
	if (!IS_ERR(sock))
		return sock;
	return ERR_PTR(-ENOTSOCK);
}