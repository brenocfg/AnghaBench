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
typedef  int /*<<< orphan*/  u64 ;
struct socket {int /*<<< orphan*/  sk; } ;
struct bpf_sk_storage_data {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct bpf_sk_storage_data*) ; 
 struct bpf_sk_storage_data* sk_storage_update (int /*<<< orphan*/ ,struct bpf_map*,void*,int /*<<< orphan*/ ) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 

__attribute__((used)) static int bpf_fd_sk_storage_update_elem(struct bpf_map *map, void *key,
					 void *value, u64 map_flags)
{
	struct bpf_sk_storage_data *sdata;
	struct socket *sock;
	int fd, err;

	fd = *(int *)key;
	sock = sockfd_lookup(fd, &err);
	if (sock) {
		sdata = sk_storage_update(sock->sk, map, value, map_flags);
		sockfd_put(sock);
		return PTR_ERR_OR_ZERO(sdata);
	}

	return err;
}