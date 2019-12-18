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
struct descriptor {struct descriptor* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_INVALID_SQL_DESCRIPTOR_NAME ; 
 int /*<<< orphan*/  ECPG_UNKNOWN_DESCRIPTOR ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 int /*<<< orphan*/  descriptor_free (struct descriptor*) ; 
 int /*<<< orphan*/  ecpg_init_sqlca (struct sqlca_t*) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 struct descriptor* get_descriptors () ; 
 int /*<<< orphan*/  set_descriptors (struct descriptor*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

bool
ECPGdeallocate_desc(int line, const char *name)
{
	struct descriptor *desc;
	struct descriptor *prev;
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_raise(line, ECPG_OUT_OF_MEMORY,
				   ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return false;
	}

	ecpg_init_sqlca(sqlca);
	for (desc = get_descriptors(), prev = NULL; desc; prev = desc, desc = desc->next)
	{
		if (strcmp(name, desc->name) == 0)
		{
			if (prev)
				prev->next = desc->next;
			else
				set_descriptors(desc->next);
			descriptor_free(desc);
			return true;
		}
	}
	ecpg_raise(line, ECPG_UNKNOWN_DESCRIPTOR, ECPG_SQLSTATE_INVALID_SQL_DESCRIPTOR_NAME, name);
	return false;
}