#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_psock_link {int /*<<< orphan*/  link_raw; TYPE_1__* map; } ;
struct TYPE_3__ {int map_type; } ;

/* Variables and functions */
#define  BPF_MAP_TYPE_SOCKHASH 129 
#define  BPF_MAP_TYPE_SOCKMAP 128 
 void sock_hash_delete_from_link (TYPE_1__*,struct sock*,int /*<<< orphan*/ ) ; 
 void sock_map_delete_from_link (TYPE_1__*,struct sock*,int /*<<< orphan*/ ) ; 

void sk_psock_unlink(struct sock *sk, struct sk_psock_link *link)
{
	switch (link->map->map_type) {
	case BPF_MAP_TYPE_SOCKMAP:
		return sock_map_delete_from_link(link->map, sk,
						 link->link_raw);
	case BPF_MAP_TYPE_SOCKHASH:
		return sock_hash_delete_from_link(link->map, sk,
						  link->link_raw);
	default:
		break;
	}
}