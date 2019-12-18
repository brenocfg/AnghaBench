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
struct bpf_sk_storage_data {void* data; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 struct bpf_sk_storage_data* sk_storage_lookup (int /*<<< orphan*/ ,struct bpf_map*,int) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 

__attribute__((used)) static void *bpf_fd_sk_storage_lookup_elem(struct bpf_map *map, void *key)
{
	struct bpf_sk_storage_data *sdata;
	struct socket *sock;
	int fd, err;

	fd = *(int *)key;
	sock = sockfd_lookup(fd, &err);
	if (sock) {
		sdata = sk_storage_lookup(sock->sk, map, true);
		sockfd_put(sock);
		return sdata ? sdata->data : NULL;
	}

	return ERR_PTR(err);
}