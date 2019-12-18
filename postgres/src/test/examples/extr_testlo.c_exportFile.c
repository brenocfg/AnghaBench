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
typedef  int /*<<< orphan*/  PGconn ;
typedef  int Oid ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  INV_READ ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lo_close (int /*<<< orphan*/ *,int) ; 
 int lo_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lo_read (int /*<<< orphan*/ *,int,char*,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
exportFile(PGconn *conn, Oid lobjId, char *filename)
{
	int			lobj_fd;
	char		buf[BUFSIZE];
	int			nbytes,
				tmp;
	int			fd;

	/*
	 * open the large object
	 */
	lobj_fd = lo_open(conn, lobjId, INV_READ);
	if (lobj_fd < 0)
		fprintf(stderr, "cannot open large object %u", lobjId);

	/*
	 * open the file to be written to
	 */
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
	{							/* error */
		fprintf(stderr, "cannot open unix file\"%s\"",
				filename);
	}

	/*
	 * read in from the inversion file and write to the Unix file
	 */
	while ((nbytes = lo_read(conn, lobj_fd, buf, BUFSIZE)) > 0)
	{
		tmp = write(fd, buf, nbytes);
		if (tmp < nbytes)
		{
			fprintf(stderr, "error while writing \"%s\"",
					filename);
		}
	}

	lo_close(conn, lobj_fd);
	close(fd);

	return;
}