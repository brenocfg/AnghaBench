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
typedef  scalar_t__ uid_t ;
struct stat {long st_size; scalar_t__ st_mtime; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned int S_IFREG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 int fwrite (char*,long,int,int /*<<< orphan*/ ) ; 
 int ino ; 
 char* malloc (long) ; 
 long offset ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_hdr (char*) ; 
 int /*<<< orphan*/  push_pad () ; 
 int /*<<< orphan*/  push_string (char const*) ; 
 int read (int,char*,long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,unsigned int,long,long,unsigned int,long,long,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 

__attribute__((used)) static int cpio_mkfile(const char *name, const char *location,
			unsigned int mode, uid_t uid, gid_t gid,
			unsigned int nlinks)
{
	char s[256];
	char *filebuf = NULL;
	struct stat buf;
	long size;
	int file = -1;
	int retval;
	int rc = -1;
	int namesize;
	unsigned int i;

	mode |= S_IFREG;

	file = open (location, O_RDONLY);
	if (file < 0) {
		fprintf (stderr, "File %s could not be opened for reading\n", location);
		goto error;
	}

	retval = fstat(file, &buf);
	if (retval) {
		fprintf(stderr, "File %s could not be stat()'ed\n", location);
		goto error;
	}

	filebuf = malloc(buf.st_size);
	if (!filebuf) {
		fprintf (stderr, "out of memory\n");
		goto error;
	}

	retval = read (file, filebuf, buf.st_size);
	if (retval < 0) {
		fprintf (stderr, "Can not read %s file\n", location);
		goto error;
	}

	size = 0;
	for (i = 1; i <= nlinks; i++) {
		/* data goes on last link */
		if (i == nlinks) size = buf.st_size;

		if (name[0] == '/')
			name++;
		namesize = strlen(name) + 1;
		sprintf(s,"%s%08X%08X%08lX%08lX%08X%08lX"
		       "%08lX%08X%08X%08X%08X%08X%08X",
			"070701",		/* magic */
			ino,			/* ino */
			mode,			/* mode */
			(long) uid,		/* uid */
			(long) gid,		/* gid */
			nlinks,			/* nlink */
			(long) buf.st_mtime,	/* mtime */
			size,			/* filesize */
			3,			/* major */
			1,			/* minor */
			0,			/* rmajor */
			0,			/* rminor */
			namesize,		/* namesize */
			0);			/* chksum */
		push_hdr(s);
		push_string(name);
		push_pad();

		if (size) {
			if (fwrite(filebuf, size, 1, stdout) != 1) {
				fprintf(stderr, "writing filebuf failed\n");
				goto error;
			}
			offset += size;
			push_pad();
		}

		name += namesize;
	}
	ino++;
	rc = 0;
	
error:
	if (filebuf) free(filebuf);
	if (file >= 0) close(file);
	return rc;
}