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
struct ceph_connection {int out_kvec_left; int out_skip; size_t out_kvec_bytes; TYPE_1__* out_kvec; } ;
struct TYPE_2__ {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void con_out_kvec_add(struct ceph_connection *con,
				size_t size, void *data)
{
	int index = con->out_kvec_left;

	BUG_ON(con->out_skip);
	BUG_ON(index >= ARRAY_SIZE(con->out_kvec));

	con->out_kvec[index].iov_len = size;
	con->out_kvec[index].iov_base = data;
	con->out_kvec_left++;
	con->out_kvec_bytes += size;
}