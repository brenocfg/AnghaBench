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
typedef  int uid_t ;
typedef  int time_t ;
typedef  int pgoff_t ;
typedef  int mode_t ;
typedef  int gid_t ;
typedef  enum tarError { ____Placeholder_tarError } tarError ;

/* Variables and functions */
 int Min (int,int) ; 
 scalar_t__ S_ISDIR (int) ; 
 int TAR_NAME_TOO_LONG ; 
 int TAR_OK ; 
 int TAR_SYMLINK_TOO_LONG ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_tar_number (char*,int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int tarChecksum (char*) ; 

enum tarError
tarCreateHeader(char *h, const char *filename, const char *linktarget,
				pgoff_t size, mode_t mode, uid_t uid, gid_t gid, time_t mtime)
{
	if (strlen(filename) > 99)
		return TAR_NAME_TOO_LONG;

	if (linktarget && strlen(linktarget) > 99)
		return TAR_SYMLINK_TOO_LONG;

	memset(h, 0, 512);			/* assume tar header size */

	/* Name 100 */
	strlcpy(&h[0], filename, 100);
	if (linktarget != NULL || S_ISDIR(mode))
	{
		/*
		 * We only support symbolic links to directories, and this is
		 * indicated in the tar format by adding a slash at the end of the
		 * name, the same as for regular directories.
		 */
		int			flen = strlen(filename);

		flen = Min(flen, 99);
		h[flen] = '/';
		h[flen + 1] = '\0';
	}

	/* Mode 8 - this doesn't include the file type bits (S_IFMT)  */
	print_tar_number(&h[100], 8, (mode & 07777));

	/* User ID 8 */
	print_tar_number(&h[108], 8, uid);

	/* Group 8 */
	print_tar_number(&h[116], 8, gid);

	/* File size 12 */
	if (linktarget != NULL || S_ISDIR(mode))
		/* Symbolic link or directory has size zero */
		print_tar_number(&h[124], 12, 0);
	else
		print_tar_number(&h[124], 12, size);

	/* Mod Time 12 */
	print_tar_number(&h[136], 12, mtime);

	/* Checksum 8 cannot be calculated until we've filled all other fields */

	if (linktarget != NULL)
	{
		/* Type - Symbolic link */
		h[156] = '2';
		/* Link Name 100 */
		strlcpy(&h[157], linktarget, 100);
	}
	else if (S_ISDIR(mode))
	{
		/* Type - directory */
		h[156] = '5';
	}
	else
	{
		/* Type - regular file */
		h[156] = '0';
	}

	/* Magic 6 */
	strcpy(&h[257], "ustar");

	/* Version 2 */
	memcpy(&h[263], "00", 2);

	/* User 32 */
	/* XXX: Do we need to care about setting correct username? */
	strlcpy(&h[265], "postgres", 32);

	/* Group 32 */
	/* XXX: Do we need to care about setting correct group name? */
	strlcpy(&h[297], "postgres", 32);

	/* Major Dev 8 */
	print_tar_number(&h[329], 8, 0);

	/* Minor Dev 8 */
	print_tar_number(&h[337], 8, 0);

	/* Prefix 155 - not used, leave as nulls */

	/* Finally, compute and insert the checksum */
	print_tar_number(&h[148], 8, tarChecksum(h));

	return TAR_OK;
}