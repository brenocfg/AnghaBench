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
struct sock {int dummy; } ;
struct request_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip4; } ;
struct flowi {TYPE_1__ u; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* inet_csk_route_req (struct sock const*,int /*<<< orphan*/ *,struct request_sock const*) ; 

__attribute__((used)) static struct dst_entry *tcp_v4_route_req(const struct sock *sk,
					  struct flowi *fl,
					  const struct request_sock *req)
{
	return inet_csk_route_req(sk, &fl->u.ip4, req);
}