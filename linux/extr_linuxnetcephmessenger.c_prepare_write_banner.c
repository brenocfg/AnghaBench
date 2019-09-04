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
struct ceph_connection {scalar_t__ out_more; TYPE_1__* msgr; } ;
struct TYPE_2__ {int /*<<< orphan*/  my_enc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CEPH_BANNER ; 
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 int /*<<< orphan*/  con_flag_set (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_out_kvec_add (struct ceph_connection*,int,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_write_banner(struct ceph_connection *con)
{
	con_out_kvec_add(con, strlen(CEPH_BANNER), CEPH_BANNER);
	con_out_kvec_add(con, sizeof (con->msgr->my_enc_addr),
					&con->msgr->my_enc_addr);

	con->out_more = 0;
	con_flag_set(con, CON_FLAG_WRITE_PENDING);
}