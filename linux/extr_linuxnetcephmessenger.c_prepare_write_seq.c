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
struct ceph_connection {int /*<<< orphan*/  out_temp_ack; int /*<<< orphan*/  in_seq_acked; int /*<<< orphan*/  in_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 int /*<<< orphan*/  con_flag_set (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_out_kvec_add (struct ceph_connection*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_out_kvec_reset (struct ceph_connection*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_write_seq(struct ceph_connection *con)
{
	dout("prepare_write_seq %p %llu -> %llu\n", con,
	     con->in_seq_acked, con->in_seq);
	con->in_seq_acked = con->in_seq;

	con_out_kvec_reset(con);

	con->out_temp_ack = cpu_to_le64(con->in_seq_acked);
	con_out_kvec_add(con, sizeof (con->out_temp_ack),
			 &con->out_temp_ack);

	con_flag_set(con, CON_FLAG_WRITE_PENDING);
}