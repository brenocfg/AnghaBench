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
typedef  scalar_t__ zend_off_t ;
struct magic_set {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ FINFO_LSEEK_FUNC (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  file_badseek (struct magic_set*) ; 
 int /*<<< orphan*/  file_error (struct magic_set*,int,char*) ; 
 char* mktemp (char*) ; 
 int open (char*,int,int) ; 
 int sread (int,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int swrite (int,char*,size_t) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
file_pipe2file(struct magic_set *ms, int fd, const void *startbuf,
    size_t nbytes)
{
	char buf[4096];
	ssize_t r;
	int tfd;

	(void)strlcpy(buf, "/tmp/file.XXXXXX", sizeof buf);
#ifndef HAVE_MKSTEMP
	{
		char *ptr = mktemp(buf);
		tfd = open(ptr, O_RDWR|O_TRUNC|O_EXCL|O_CREAT, 0600);
		r = errno;
		(void)unlink(ptr);
		errno = r;
	}
#else
	{
		int te;
		tfd = mkstemp(buf);
		te = errno;
		(void)unlink(buf);
		errno = te;
	}
#endif
	if (tfd == -1) {
		file_error(ms, errno,
		    "cannot create temporary file for pipe copy");
		return -1;
	}

	if (swrite(tfd, startbuf, nbytes) != (ssize_t)nbytes)
		r = 1;
	else {
		while ((r = sread(fd, buf, sizeof(buf), 1)) > 0)
			if (swrite(tfd, buf, (size_t)r) != r)
				break;
	}

	switch (r) {
	case -1:
		file_error(ms, errno, "error copying from pipe to temp file");
		return -1;
	case 0:
		break;
	default:
		file_error(ms, errno, "error while writing to temp file");
		return -1;
	}

	/*
	 * We duplicate the file descriptor, because fclose on a
	 * tmpfile will delete the file, but any open descriptors
	 * can still access the phantom inode.
	 */
	if ((fd = dup2(tfd, fd)) == -1) {
		file_error(ms, errno, "could not dup descriptor for temp file");
		return -1;
	}
	(void)close(tfd);
	if (FINFO_LSEEK_FUNC(fd, (zend_off_t)0, SEEK_SET) == (zend_off_t)-1) {
		file_badseek(ms);
		return -1;
	}
	return fd;
}