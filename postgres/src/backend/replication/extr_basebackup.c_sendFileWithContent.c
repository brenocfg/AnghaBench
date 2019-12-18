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
struct stat {int st_size; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_mtime; scalar_t__ st_gid; scalar_t__ st_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _tarWriteHeader (char const*,int /*<<< orphan*/ *,struct stat*,int) ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  pg_file_create_mode ; 
 int /*<<< orphan*/  pq_putmessage (char,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sendFileWithContent(const char *filename, const char *content)
{
	struct stat statbuf;
	int			pad,
				len;

	len = strlen(content);

	/*
	 * Construct a stat struct for the backup_label file we're injecting in
	 * the tar.
	 */
	/* Windows doesn't have the concept of uid and gid */
#ifdef WIN32
	statbuf.st_uid = 0;
	statbuf.st_gid = 0;
#else
	statbuf.st_uid = geteuid();
	statbuf.st_gid = getegid();
#endif
	statbuf.st_mtime = time(NULL);
	statbuf.st_mode = pg_file_create_mode;
	statbuf.st_size = len;

	_tarWriteHeader(filename, NULL, &statbuf, false);
	/* Send the contents as a CopyData message */
	pq_putmessage('d', content, len);

	/* Pad to 512 byte boundary, per tar format requirements */
	pad = ((len + 511) & ~511) - len;
	if (pad > 0)
	{
		char		buf[512];

		MemSet(buf, 0, pad);
		pq_putmessage('d', buf, pad);
	}
}