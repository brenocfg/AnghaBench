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
struct rds_sock {int dummy; } ;
struct rds_connection {int c_npaths; int /*<<< orphan*/  c_hs_waitq; } ;

/* Variables and functions */
 int RDS_MPATH_HASH (struct rds_sock*,int) ; 
 int RDS_MPATH_WORKERS ; 
 int /*<<< orphan*/  rds_send_ping (struct rds_connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rds_send_mprds_hash(struct rds_sock *rs,
			       struct rds_connection *conn, int nonblock)
{
	int hash;

	if (conn->c_npaths == 0)
		hash = RDS_MPATH_HASH(rs, RDS_MPATH_WORKERS);
	else
		hash = RDS_MPATH_HASH(rs, conn->c_npaths);
	if (conn->c_npaths == 0 && hash != 0) {
		rds_send_ping(conn, 0);

		/* The underlying connection is not up yet.  Need to wait
		 * until it is up to be sure that the non-zero c_path can be
		 * used.  But if we are interrupted, we have to use the zero
		 * c_path in case the connection ends up being non-MP capable.
		 */
		if (conn->c_npaths == 0) {
			/* Cannot wait for the connection be made, so just use
			 * the base c_path.
			 */
			if (nonblock)
				return 0;
			if (wait_event_interruptible(conn->c_hs_waitq,
						     conn->c_npaths != 0))
				hash = 0;
		}
		if (conn->c_npaths == 1)
			hash = 0;
	}
	return hash;
}