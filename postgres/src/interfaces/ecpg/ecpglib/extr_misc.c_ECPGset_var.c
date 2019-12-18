#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct var_list {int number; struct var_list* next; void* pointer; } ;
struct TYPE_2__ {int /*<<< orphan*/  sqlerrmc; int /*<<< orphan*/  sqlerrml; } ;
struct sqlca_t {TYPE_1__ sqlerrm; int /*<<< orphan*/  sqlstate; int /*<<< orphan*/  sqlcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPGfree_auto_mem () ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 scalar_t__ calloc (long,int) ; 
 int /*<<< orphan*/  ecpg_init_sqlca (struct sqlca_t*) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct var_list* ivlist ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

void
ECPGset_var(int number, void *pointer, int lineno)
{
	struct var_list *ptr;

	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_raise(lineno, ECPG_OUT_OF_MEMORY,
				   ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return;
	}

	ecpg_init_sqlca(sqlca);

	for (ptr = ivlist; ptr != NULL; ptr = ptr->next)
	{
		if (ptr->number == number)
		{
			/* already known => just change pointer value */
			ptr->pointer = pointer;
			return;
		}
	}

	/* a new one has to be added */
	ptr = (struct var_list *) calloc(1L, sizeof(struct var_list));
	if (!ptr)
	{
		struct sqlca_t *sqlca = ECPGget_sqlca();

		if (sqlca == NULL)
		{
			ecpg_raise(lineno, ECPG_OUT_OF_MEMORY,
					   ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
			return;
		}

		sqlca->sqlcode = ECPG_OUT_OF_MEMORY;
		strncpy(sqlca->sqlstate, "YE001", sizeof(sqlca->sqlstate));
		snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc), "out of memory on line %d", lineno);
		sqlca->sqlerrm.sqlerrml = strlen(sqlca->sqlerrm.sqlerrmc);
		/* free all memory we have allocated for the user */
		ECPGfree_auto_mem();
	}
	else
	{
		ptr->number = number;
		ptr->pointer = pointer;
		ptr->next = ivlist;
		ivlist = ptr;
	}
}