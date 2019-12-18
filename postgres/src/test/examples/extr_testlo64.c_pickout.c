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
 int /*<<< orphan*/  INV_READ ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lo_close (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lo_lseek64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lo_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lo_read (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  lo_tell64 (int /*<<< orphan*/ *,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
pickout(PGconn *conn, Oid lobjId, pg_int64 start, int len)
{
	int			lobj_fd;
	char	   *buf;
	int			nbytes;
	int			nread;

	lobj_fd = lo_open(conn, lobjId, INV_READ);
	if (lobj_fd < 0)
		fprintf(stderr, "cannot open large object %u", lobjId);

	if (lo_lseek64(conn, lobj_fd, start, SEEK_SET) < 0)
		fprintf(stderr, "error in lo_lseek64: %s", PQerrorMessage(conn));

	if (lo_tell64(conn, lobj_fd) != start)
		fprintf(stderr, "error in lo_tell64: %s", PQerrorMessage(conn));

	buf = malloc(len + 1);

	nread = 0;
	while (len - nread > 0)
	{
		nbytes = lo_read(conn, lobj_fd, buf, len - nread);
		buf[nbytes] = '\0';
		fprintf(stderr, ">>> %s", buf);
		nread += nbytes;
		if (nbytes <= 0)
			break;				/* no more data? */
	}
	free(buf);
	fprintf(stderr, "\n");
	lo_close(conn, lobj_fd);
}