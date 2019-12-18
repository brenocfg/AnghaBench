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
struct socket {int /*<<< orphan*/  sk; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int sk_storage_delete (int /*<<< orphan*/ ,struct bpf_map*) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 

__attribute__((used)) static int bpf_fd_sk_storage_delete_elem(struct bpf_map *map, void *key)
{
	struct socket *sock;
	int fd, err;

	fd = *(int *)key;
	sock = sockfd_lookup(fd, &err);
	if (sock) {
		err = sk_storage_delete(sock->sk, map);
		sockfd_put(sock);
		return err;
	}

	return err;
}