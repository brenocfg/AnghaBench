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
typedef  union VALUETYPE {int dummy; } VALUETYPE ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  RMagic ;

/* Variables and functions */
 scalar_t__ HOWMANY ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_and_restore (int /*<<< orphan*/ *,char const*,int,struct stat*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ errno ; 
 int file_buffer (int /*<<< orphan*/ *,int,char const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  file_error (int /*<<< orphan*/ *,scalar_t__,char*,char const*) ; 
 int file_fsmagic (int /*<<< orphan*/ *,char const*,struct stat*) ; 
 char const* file_getbuffer (int /*<<< orphan*/ *) ; 
 int file_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int info_from_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int) ; 
 int read (int,char*,scalar_t__) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static const char *file_or_fd(RMagic *ms, const char *inname, int fd) {
	int ispipe = 0, rv = -1;
	unsigned char *buf;
	struct stat sb;
	int  nbytes = 0;	/* number of bytes read from a datafile */

	/*
	 * one extra for terminating '\0', and
	 * some overlapping space for matches near EOF
	 */
#define SLOP (1 + sizeof(union VALUETYPE))
	if (!(buf = malloc (HOWMANY + SLOP))) {
		return NULL;
	}

	if (file_reset (ms) == -1) {
		goto done;
	}

	switch (file_fsmagic (ms, inname, &sb)) {
	case -1: goto done;		/* error */
	case 0:	break;			/* nothing found */
	default: rv = 0; goto done;	/* matched it and printed type */
	}

	if (!inname) {
		if (fstat (fd, &sb) == 0 && S_ISFIFO (sb.st_mode)) {
			ispipe = 1;
		}
	} else {
		int flags = O_RDONLY|O_BINARY;

		if (stat (inname, &sb) == 0 && S_ISFIFO (sb.st_mode)) {
#if O_NONBLOCK
			flags |= O_NONBLOCK;
#endif
			ispipe = 1;
		}
		errno = 0;
		if ((fd = open (inname, flags)) < 0) {
			eprintf ("couldn't open file\n");
			if (info_from_stat (ms, sb.st_mode) == -1) {
				goto done;
			}
			rv = 0;
			goto done;
		}
#ifdef O_NONBLOCK
		if ((flags = fcntl (fd, F_GETFL)) != -1) {
			flags &= ~O_NONBLOCK;
			(void)fcntl (fd, F_SETFL, flags);
		}
#endif
	}

	/*
	 * try looking at the first HOWMANY bytes
	 */
#ifdef O_NONBLOCK
	if (ispipe) {
		ssize_t r = 0;

		//while ((r = sread(fd, (void *)&buf[nbytes],
		while ((r = read(fd, (void *)&buf[nbytes],
		    (size_t)(HOWMANY - nbytes))) > 0) {
			nbytes += r;
			if (r < PIPE_BUF) {
				break;
			}
		}

		if (nbytes == 0) {
			/* We can not read it, but we were able to stat it. */
			if (info_from_stat (ms, sb.st_mode) == -1) {
				goto done;
			}
			rv = 0;
			goto done;
		}
	} else {
#endif
		if ((nbytes = read(fd, (char *)buf, HOWMANY)) == -1) {
			file_error(ms, errno, "cannot read `%s'", inname);
			goto done;
		}
#ifdef O_NONBLOCK
	}
#endif

	(void)memset (buf + nbytes, 0, SLOP); /* NUL terminate */
	if (file_buffer (ms, fd, inname, buf, (size_t)nbytes) == -1) {
		goto done;
	}
	rv = 0;
done:
	free (buf);
	close_and_restore (ms, inname, fd, &sb);
	return rv == 0 ? file_getbuffer(ms) : NULL;
}