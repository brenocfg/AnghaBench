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
 int /*<<< orphan*/  INV_WRITE ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lo_close (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lo_lseek64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lo_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lo_write (int /*<<< orphan*/ *,int,char*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
overwrite(PGconn *conn, Oid lobjId, pg_int64 start, int len)
{
	int			lobj_fd;
	char	   *buf;
	int			nbytes;
	int			nwritten;
	int			i;

	lobj_fd = lo_open(conn, lobjId, INV_WRITE);
	if (lobj_fd < 0)
		fprintf(stderr, "cannot open large object %u", lobjId);

	if (lo_lseek64(conn, lobj_fd, start, SEEK_SET) < 0)
		fprintf(stderr, "error in lo_lseek64: %s", PQerrorMessage(conn));

	buf = malloc(len + 1);

	for (i = 0; i < len; i++)
		buf[i] = 'X';
	buf[i] = '\0';

	nwritten = 0;
	while (len - nwritten > 0)
	{
		nbytes = lo_write(conn, lobj_fd, buf + nwritten, len - nwritten);
		nwritten += nbytes;
		if (nbytes <= 0)
		{
			fprintf(stderr, "\nWRITE FAILED!\n");
			break;
		}
	}
	free(buf);
	fprintf(stderr, "\n");
	lo_close(conn, lobj_fd);
}