#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  old_file ;
typedef  int /*<<< orphan*/  new_file ;
typedef  int /*<<< orphan*/  extent_suffix ;
struct TYPE_5__ {int transfer_mode; } ;
struct TYPE_4__ {char* old_tablespace; int old_tablespace_suffix; int old_db_oid; char* old_relfilenode; char* new_tablespace; int new_tablespace_suffix; int new_db_oid; char* new_relfilenode; int /*<<< orphan*/  relname; int /*<<< orphan*/  nspname; } ;
typedef  TYPE_1__ FileNameMap ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_STATUS ; 
 int /*<<< orphan*/  PG_VERBOSE ; 
#define  TRANSFER_MODE_CLONE 130 
#define  TRANSFER_MODE_COPY 129 
#define  TRANSFER_MODE_LINK 128 
 int /*<<< orphan*/  cloneFile (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyFile (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  linkFile (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  rewriteVisibilityMap (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 TYPE_2__ user_opts ; 

__attribute__((used)) static void
transfer_relfile(FileNameMap *map, const char *type_suffix, bool vm_must_add_frozenbit)
{
	char		old_file[MAXPGPATH];
	char		new_file[MAXPGPATH];
	int			segno;
	char		extent_suffix[65];
	struct stat statbuf;

	/*
	 * Now copy/link any related segments as well. Remember, PG breaks large
	 * files into 1GB segments, the first segment has no extension, subsequent
	 * segments are named relfilenode.1, relfilenode.2, relfilenode.3.
	 */
	for (segno = 0;; segno++)
	{
		if (segno == 0)
			extent_suffix[0] = '\0';
		else
			snprintf(extent_suffix, sizeof(extent_suffix), ".%d", segno);

		snprintf(old_file, sizeof(old_file), "%s%s/%u/%u%s%s",
				 map->old_tablespace,
				 map->old_tablespace_suffix,
				 map->old_db_oid,
				 map->old_relfilenode,
				 type_suffix,
				 extent_suffix);
		snprintf(new_file, sizeof(new_file), "%s%s/%u/%u%s%s",
				 map->new_tablespace,
				 map->new_tablespace_suffix,
				 map->new_db_oid,
				 map->new_relfilenode,
				 type_suffix,
				 extent_suffix);

		/* Is it an extent, fsm, or vm file? */
		if (type_suffix[0] != '\0' || segno != 0)
		{
			/* Did file open fail? */
			if (stat(old_file, &statbuf) != 0)
			{
				/* File does not exist?  That's OK, just return */
				if (errno == ENOENT)
					return;
				else
					pg_fatal("error while checking for file existence \"%s.%s\" (\"%s\" to \"%s\"): %s\n",
							 map->nspname, map->relname, old_file, new_file,
							 strerror(errno));
			}

			/* If file is empty, just return */
			if (statbuf.st_size == 0)
				return;
		}

		unlink(new_file);

		/* Copying files might take some time, so give feedback. */
		pg_log(PG_STATUS, "%s", old_file);

		if (vm_must_add_frozenbit && strcmp(type_suffix, "_vm") == 0)
		{
			/* Need to rewrite visibility map format */
			pg_log(PG_VERBOSE, "rewriting \"%s\" to \"%s\"\n",
				   old_file, new_file);
			rewriteVisibilityMap(old_file, new_file, map->nspname, map->relname);
		}
		else
			switch (user_opts.transfer_mode)
			{
				case TRANSFER_MODE_CLONE:
					pg_log(PG_VERBOSE, "cloning \"%s\" to \"%s\"\n",
						   old_file, new_file);
					cloneFile(old_file, new_file, map->nspname, map->relname);
					break;
				case TRANSFER_MODE_COPY:
					pg_log(PG_VERBOSE, "copying \"%s\" to \"%s\"\n",
						   old_file, new_file);
					copyFile(old_file, new_file, map->nspname, map->relname);
					break;
				case TRANSFER_MODE_LINK:
					pg_log(PG_VERBOSE, "linking \"%s\" to \"%s\"\n",
						   old_file, new_file);
					linkFile(old_file, new_file, map->nspname, map->relname);
			}
	}
}