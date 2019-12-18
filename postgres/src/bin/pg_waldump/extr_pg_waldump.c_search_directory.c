#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dirent {char const* d_name; } ;
typedef  TYPE_1__* XLogLongPageHeader ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  xlp_seg_size; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__ PGAlignedXLogBlock ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  IsValidWalSegSize (int /*<<< orphan*/ ) ; 
 scalar_t__ IsXLogFileName (char const*) ; 
 int /*<<< orphan*/  WalSegSz ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal_error (char*,char const*,int,...) ; 
 int /*<<< orphan*/  ngettext (char*,char*,int /*<<< orphan*/ ) ; 
 int open_file_in_directory (char const*,char const*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static bool
search_directory(const char *directory, const char *fname)
{
	int			fd = -1;
	DIR		   *xldir;

	/* open file if valid filename is provided */
	if (fname != NULL)
		fd = open_file_in_directory(directory, fname);

	/*
	 * A valid file name is not passed, so search the complete directory.  If
	 * we find any file whose name is a valid WAL file name then try to open
	 * it.  If we cannot open it, bail out.
	 */
	else if ((xldir = opendir(directory)) != NULL)
	{
		struct dirent *xlde;

		while ((xlde = readdir(xldir)) != NULL)
		{
			if (IsXLogFileName(xlde->d_name))
			{
				fd = open_file_in_directory(directory, xlde->d_name);
				fname = xlde->d_name;
				break;
			}
		}

		closedir(xldir);
	}

	/* set WalSegSz if file is successfully opened */
	if (fd >= 0)
	{
		PGAlignedXLogBlock buf;
		int			r;

		r = read(fd, buf.data, XLOG_BLCKSZ);
		if (r == XLOG_BLCKSZ)
		{
			XLogLongPageHeader longhdr = (XLogLongPageHeader) buf.data;

			WalSegSz = longhdr->xlp_seg_size;

			if (!IsValidWalSegSize(WalSegSz))
				fatal_error(ngettext("WAL segment size must be a power of two between 1 MB and 1 GB, but the WAL file \"%s\" header specifies %d byte",
									 "WAL segment size must be a power of two between 1 MB and 1 GB, but the WAL file \"%s\" header specifies %d bytes",
									 WalSegSz),
							fname, WalSegSz);
		}
		else
		{
			if (errno != 0)
				fatal_error("could not read file \"%s\": %s",
							fname, strerror(errno));
			else
				fatal_error("could not read file \"%s\": read %d of %zu",
							fname, r, (Size) XLOG_BLCKSZ);
		}
		close(fd);
		return true;
	}

	return false;
}