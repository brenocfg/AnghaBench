#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* path; void* oid; } ;
typedef  TYPE_1__ tablespaceinfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ENOENT ; 
 int EOF ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ FreeFile (int /*<<< orphan*/ *) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  TABLESPACE_MAP ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 
 void* pstrdup (char*) ; 
 int sscanf (char*,char*,char*,int*) ; 

__attribute__((used)) static bool
read_tablespace_map(List **tablespaces)
{
	tablespaceinfo *ti;
	FILE	   *lfp;
	char		tbsoid[MAXPGPATH];
	char	   *tbslinkpath;
	char		str[MAXPGPATH];
	int			ch,
				prev_ch = -1,
				i = 0,
				n;

	/*
	 * See if tablespace_map file is present
	 */
	lfp = AllocateFile(TABLESPACE_MAP, "r");
	if (!lfp)
	{
		if (errno != ENOENT)
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m",
							TABLESPACE_MAP)));
		return false;			/* it's not there, all is fine */
	}

	/*
	 * Read and parse the link name and path lines from tablespace_map file
	 * (this code is pretty crude, but we are not expecting any variability in
	 * the file format).  While taking backup we embed escape character '\\'
	 * before newline in tablespace path, so that during reading of
	 * tablespace_map file, we could distinguish newline in tablespace path
	 * and end of line.  Now while reading tablespace_map file, remove the
	 * escape character that has been added in tablespace path during backup.
	 */
	while ((ch = fgetc(lfp)) != EOF)
	{
		if ((ch == '\n' || ch == '\r') && prev_ch != '\\')
		{
			str[i] = '\0';
			if (sscanf(str, "%s %n", tbsoid, &n) != 1)
				ereport(FATAL,
						(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						 errmsg("invalid data in file \"%s\"", TABLESPACE_MAP)));
			tbslinkpath = str + n;
			i = 0;

			ti = palloc(sizeof(tablespaceinfo));
			ti->oid = pstrdup(tbsoid);
			ti->path = pstrdup(tbslinkpath);

			*tablespaces = lappend(*tablespaces, ti);
			continue;
		}
		else if ((ch == '\n' || ch == '\r') && prev_ch == '\\')
			str[i - 1] = ch;
		else
			str[i++] = ch;
		prev_ch = ch;
	}

	if (ferror(lfp) || FreeFile(lfp))
		ereport(FATAL,
				(errcode_for_file_access(),
				 errmsg("could not read file \"%s\": %m",
						TABLESPACE_MAP)));

	return true;
}