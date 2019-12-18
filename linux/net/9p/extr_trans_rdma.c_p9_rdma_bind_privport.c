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
typedef  int /*<<< orphan*/  ushort ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct p9_trans_rdma {int /*<<< orphan*/  cm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int P9_DEF_MAX_RESVPORT ; 
 int P9_DEF_MIN_RESVPORT ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int rdma_bind_addr (int /*<<< orphan*/ ,struct sockaddr*) ; 

__attribute__((used)) static int p9_rdma_bind_privport(struct p9_trans_rdma *rdma)
{
	struct sockaddr_in cl = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_ANY),
	};
	int port, err = -EINVAL;

	for (port = P9_DEF_MAX_RESVPORT; port >= P9_DEF_MIN_RESVPORT; port--) {
		cl.sin_port = htons((ushort)port);
		err = rdma_bind_addr(rdma->cm_id, (struct sockaddr *)&cl);
		if (err != -EADDRINUSE)
			break;
	}
	return err;
}