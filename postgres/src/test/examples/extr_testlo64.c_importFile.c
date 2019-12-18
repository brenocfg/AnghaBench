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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int BUFSIZE ; 
 int INV_READ ; 
 int INV_WRITE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lo_close (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lo_creat (int /*<<< orphan*/ *,int) ; 
 int lo_open (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int lo_write (int /*<<< orphan*/ *,int,char*,int) ; 
 int open (char*,int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static Oid
importFile(PGconn *conn, char *filename)
{
	Oid			lobjId;
	int			lobj_fd;
	char		buf[BUFSIZE];
	int			nbytes,
				tmp;
	int			fd;

	/*
	 * open the file to be read in
	 */
	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
	{							/* error */
		fprintf(stderr, "cannot open unix file\"%s\"\n", filename);
	}

	/*
	 * create the large object
	 */
	lobjId = lo_creat(conn, INV_READ | INV_WRITE);
	if (lobjId == 0)
		fprintf(stderr, "cannot create large object");

	lobj_fd = lo_open(conn, lobjId, INV_WRITE);

	/*
	 * read in from the Unix file and write to the inversion file
	 */
	while ((nbytes = read(fd, buf, BUFSIZE)) > 0)
	{
		tmp = lo_write(conn, lobj_fd, buf, nbytes);
		if (tmp < nbytes)
			fprintf(stderr, "error while reading \"%s\"", filename);
	}

	close(fd);
	lo_close(conn, lobj_fd);

	return lobjId;
}