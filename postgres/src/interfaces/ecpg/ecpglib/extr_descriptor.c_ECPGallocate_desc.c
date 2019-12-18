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
struct sqlca_t {int dummy; } ;
struct descriptor {int count; struct descriptor* name; int /*<<< orphan*/  result; int /*<<< orphan*/ * items; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 int /*<<< orphan*/  PQmakeEmptyPGresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct descriptor* ecpg_alloc (int,int) ; 
 int /*<<< orphan*/  ecpg_free (struct descriptor*) ; 
 int /*<<< orphan*/  ecpg_init_sqlca (struct sqlca_t*) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_descriptors () ; 
 int /*<<< orphan*/  set_descriptors (struct descriptor*) ; 
 int /*<<< orphan*/  strcpy (struct descriptor*,char const*) ; 
 int strlen (char const*) ; 

bool
ECPGallocate_desc(int line, const char *name)
{
	struct descriptor *new;
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_raise(line, ECPG_OUT_OF_MEMORY,
				   ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return false;
	}

	ecpg_init_sqlca(sqlca);
	new = (struct descriptor *) ecpg_alloc(sizeof(struct descriptor), line);
	if (!new)
		return false;
	new->next = get_descriptors();
	new->name = ecpg_alloc(strlen(name) + 1, line);
	if (!new->name)
	{
		ecpg_free(new);
		return false;
	}
	new->count = -1;
	new->items = NULL;
	new->result = PQmakeEmptyPGresult(NULL, 0);
	if (!new->result)
	{
		ecpg_free(new->name);
		ecpg_free(new);
		ecpg_raise(line, ECPG_OUT_OF_MEMORY, ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return false;
	}
	strcpy(new->name, name);
	set_descriptors(new);
	return true;
}