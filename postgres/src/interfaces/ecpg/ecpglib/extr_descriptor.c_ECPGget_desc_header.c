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
struct sqlca_t {int* sqlerrd; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecpg_init_sqlca (struct sqlca_t*) ; 
 int /*<<< orphan*/  ecpg_log (char*,int) ; 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecpg_result_by_descriptor (int,char const*) ; 

bool
ECPGget_desc_header(int lineno, const char *desc_name, int *count)
{
	PGresult   *ECPGresult;
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_raise(lineno, ECPG_OUT_OF_MEMORY,
				   ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return false;
	}

	ecpg_init_sqlca(sqlca);
	ECPGresult = ecpg_result_by_descriptor(lineno, desc_name);
	if (!ECPGresult)
		return false;

	*count = PQnfields(ECPGresult);
	sqlca->sqlerrd[2] = 1;
	ecpg_log("ECPGget_desc_header: found %d attributes\n", *count);
	return true;
}