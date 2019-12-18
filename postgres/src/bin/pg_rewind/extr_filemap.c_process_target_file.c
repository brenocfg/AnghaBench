#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  localpath ;
struct TYPE_9__ {scalar_t__ nlist; TYPE_3__* last; TYPE_3__* first; int /*<<< orphan*/  narray; int /*<<< orphan*/ * array; } ;
typedef  TYPE_2__ filemap_t ;
typedef  scalar_t__ file_type_t ;
struct TYPE_8__ {scalar_t__ bitmapsize; int /*<<< orphan*/ * bitmap; } ;
struct TYPE_10__ {char* path; size_t oldsize; char* link_target; struct TYPE_10__* next; int /*<<< orphan*/  isrelfile; TYPE_1__ pagemap; scalar_t__ newsize; int /*<<< orphan*/  action; scalar_t__ type; } ;
typedef  TYPE_3__ file_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FILE_ACTION_REMOVE ; 
 scalar_t__ FILE_TYPE_DIRECTORY ; 
 scalar_t__ FILE_TYPE_SYMLINK ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/ * bsearch (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* datadir_target ; 
 scalar_t__ errno ; 
 TYPE_2__* filemap ; 
 int /*<<< orphan*/  filemap_list_to_array (TYPE_2__*) ; 
 int /*<<< orphan*/  isRelDataFile (char const*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  path_cmp ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 TYPE_3__* pg_malloc (int) ; 
 char* pg_strdup (char const*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void
process_target_file(const char *path, file_type_t type, size_t oldsize,
					const char *link_target)
{
	bool		exists;
	char		localpath[MAXPGPATH];
	struct stat statbuf;
	file_entry_t key;
	file_entry_t *key_ptr;
	filemap_t  *map = filemap;
	file_entry_t *entry;

	/*
	 * Do not apply any exclusion filters here.  This has advantage to remove
	 * from the target data folder all paths which have been filtered out from
	 * the source data folder when processing the source files.
	 */

	snprintf(localpath, sizeof(localpath), "%s/%s", datadir_target, path);
	if (lstat(localpath, &statbuf) < 0)
	{
		if (errno != ENOENT)
			pg_fatal("could not stat file \"%s\": %m",
					 localpath);

		exists = false;
	}

	if (map->array == NULL)
	{
		/* on first call, initialize lookup array */
		if (map->nlist == 0)
		{
			/* should not happen */
			pg_fatal("source file list is empty");
		}

		filemap_list_to_array(map);

		Assert(map->array != NULL);

		qsort(map->array, map->narray, sizeof(file_entry_t *), path_cmp);
	}

	/*
	 * Like in process_source_file, pretend that xlog is always a  directory.
	 */
	if (strcmp(path, "pg_wal") == 0 && type == FILE_TYPE_SYMLINK)
		type = FILE_TYPE_DIRECTORY;

	key.path = (char *) path;
	key_ptr = &key;
	exists = (bsearch(&key_ptr, map->array, map->narray, sizeof(file_entry_t *),
					  path_cmp) != NULL);

	/* Remove any file or folder that doesn't exist in the source system. */
	if (!exists)
	{
		entry = pg_malloc(sizeof(file_entry_t));
		entry->path = pg_strdup(path);
		entry->type = type;
		entry->action = FILE_ACTION_REMOVE;
		entry->oldsize = oldsize;
		entry->newsize = 0;
		entry->link_target = link_target ? pg_strdup(link_target) : NULL;
		entry->next = NULL;
		entry->pagemap.bitmap = NULL;
		entry->pagemap.bitmapsize = 0;
		entry->isrelfile = isRelDataFile(path);

		if (map->last == NULL)
			map->first = entry;
		else
			map->last->next = entry;
		map->last = entry;
		map->nlist++;
	}
	else
	{
		/*
		 * We already handled all files that exist in the source system in
		 * process_source_file().
		 */
	}
}