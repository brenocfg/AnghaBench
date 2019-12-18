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
struct ceph_connection {int /*<<< orphan*/ * out_kvec; int /*<<< orphan*/ * out_kvec_cur; scalar_t__ out_kvec_bytes; scalar_t__ out_kvec_left; int /*<<< orphan*/  out_skip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void con_out_kvec_reset(struct ceph_connection *con)
{
	BUG_ON(con->out_skip);

	con->out_kvec_left = 0;
	con->out_kvec_bytes = 0;
	con->out_kvec_cur = &con->out_kvec[0];
}