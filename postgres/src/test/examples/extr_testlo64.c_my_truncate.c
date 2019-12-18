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
typedef  int /*<<< orphan*/  pg_int64 ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int Oid ;

/* Variables and functions */
 int INV_READ ; 
 int INV_WRITE ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lo_close (int /*<<< orphan*/ *,int) ; 
 int lo_open (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ lo_truncate64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
my_truncate(PGconn *conn, Oid lobjId, pg_int64 len)
{
	int			lobj_fd;

	lobj_fd = lo_open(conn, lobjId, INV_READ | INV_WRITE);
	if (lobj_fd < 0)
		fprintf(stderr, "cannot open large object %u", lobjId);

	if (lo_truncate64(conn, lobj_fd, len) < 0)
		fprintf(stderr, "error in lo_truncate64: %s", PQerrorMessage(conn));

	lo_close(conn, lobj_fd);
}