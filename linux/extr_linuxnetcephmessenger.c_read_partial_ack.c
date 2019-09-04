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
struct ceph_connection {int /*<<< orphan*/  in_temp_ack; } ;

/* Variables and functions */
 int read_partial (struct ceph_connection*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_partial_ack(struct ceph_connection *con)
{
	int size = sizeof (con->in_temp_ack);
	int end = size;

	return read_partial(con, end, size, &con->in_temp_ack);
}