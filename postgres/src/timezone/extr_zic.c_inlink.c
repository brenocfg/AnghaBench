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
struct link {void* l_to; void* l_from; int /*<<< orphan*/  l_linenum; int /*<<< orphan*/  l_filename; } ;

/* Variables and functions */
 size_t LF_FROM ; 
 size_t LF_TO ; 
 int LINK_FIELDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* ecpyalloc (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 struct link* growalloc (struct link*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linenum ; 
 struct link* links ; 
 int /*<<< orphan*/  namecheck (char*) ; 
 int /*<<< orphan*/  nlinks ; 
 int /*<<< orphan*/  nlinks_alloc ; 

__attribute__((used)) static void
inlink(char **fields, int nfields)
{
	struct link l;

	if (nfields != LINK_FIELDS)
	{
		error(_("wrong number of fields on Link line"));
		return;
	}
	if (*fields[LF_FROM] == '\0')
	{
		error(_("blank FROM field on Link line"));
		return;
	}
	if (!namecheck(fields[LF_TO]))
		return;
	l.l_filename = filename;
	l.l_linenum = linenum;
	l.l_from = ecpyalloc(fields[LF_FROM]);
	l.l_to = ecpyalloc(fields[LF_TO]);
	links = growalloc(links, sizeof *links, nlinks, &nlinks_alloc);
	links[nlinks++] = l;
}