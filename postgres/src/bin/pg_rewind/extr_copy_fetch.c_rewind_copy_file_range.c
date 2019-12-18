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
typedef  int /*<<< orphan*/  srcpath ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PGAlignedBlock ;

/* Variables and functions */
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ close (int) ; 
 char* datadir_source ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_target_file (char const*,int) ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  write_target_range (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
rewind_copy_file_range(const char *path, off_t begin, off_t end, bool trunc)
{
	PGAlignedBlock buf;
	char		srcpath[MAXPGPATH];
	int			srcfd;

	snprintf(srcpath, sizeof(srcpath), "%s/%s", datadir_source, path);

	srcfd = open(srcpath, O_RDONLY | PG_BINARY, 0);
	if (srcfd < 0)
		pg_fatal("could not open source file \"%s\": %m",
				 srcpath);

	if (lseek(srcfd, begin, SEEK_SET) == -1)
		pg_fatal("could not seek in source file: %m");

	open_target_file(path, trunc);

	while (end - begin > 0)
	{
		int			readlen;
		int			len;

		if (end - begin > sizeof(buf))
			len = sizeof(buf);
		else
			len = end - begin;

		readlen = read(srcfd, buf.data, len);

		if (readlen < 0)
			pg_fatal("could not read file \"%s\": %m",
					 srcpath);
		else if (readlen == 0)
			pg_fatal("unexpected EOF while reading file \"%s\"", srcpath);

		write_target_range(buf.data, begin, readlen);
		begin += readlen;
	}

	if (close(srcfd) != 0)
		pg_fatal("could not close file \"%s\": %m", srcpath);
}