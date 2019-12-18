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
struct TYPE_2__ {char* sqlerrmc; size_t sqlerrml; } ;
struct sqlca_t {TYPE_1__ sqlerrm; } ;

/* Variables and functions */
 struct sqlca_t* ECPGget_sqlca () ; 
 char* ecpg_gettext (char*) ; 
 int /*<<< orphan*/  ecpg_log (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
sqlprint(void)
{
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_log("out of memory");
		return;
	}

	sqlca->sqlerrm.sqlerrmc[sqlca->sqlerrm.sqlerrml] = '\0';
	fprintf(stderr, ecpg_gettext("SQL error: %s\n"), sqlca->sqlerrm.sqlerrmc);
}