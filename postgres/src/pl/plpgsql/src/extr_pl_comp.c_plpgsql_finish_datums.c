#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dtype; } ;
struct TYPE_5__ {int ndatums; int /*<<< orphan*/  copiable_size; TYPE_3__** datums; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  PLpgSQL_var ;
typedef  int /*<<< orphan*/  PLpgSQL_rec ;
typedef  TYPE_1__ PLpgSQL_function ;
typedef  int /*<<< orphan*/  PLpgSQL_datum ;

/* Variables and functions */
 int /*<<< orphan*/  MAXALIGN (int) ; 
#define  PLPGSQL_DTYPE_PROMISE 130 
#define  PLPGSQL_DTYPE_REC 129 
#define  PLPGSQL_DTYPE_VAR 128 
 TYPE_3__** palloc (int) ; 
 TYPE_3__** plpgsql_Datums ; 
 int plpgsql_nDatums ; 

__attribute__((used)) static void
plpgsql_finish_datums(PLpgSQL_function *function)
{
	Size		copiable_size = 0;
	int			i;

	function->ndatums = plpgsql_nDatums;
	function->datums = palloc(sizeof(PLpgSQL_datum *) * plpgsql_nDatums);
	for (i = 0; i < plpgsql_nDatums; i++)
	{
		function->datums[i] = plpgsql_Datums[i];

		/* This must agree with copy_plpgsql_datums on what is copiable */
		switch (function->datums[i]->dtype)
		{
			case PLPGSQL_DTYPE_VAR:
			case PLPGSQL_DTYPE_PROMISE:
				copiable_size += MAXALIGN(sizeof(PLpgSQL_var));
				break;
			case PLPGSQL_DTYPE_REC:
				copiable_size += MAXALIGN(sizeof(PLpgSQL_rec));
				break;
			default:
				break;
		}
	}
	function->copiable_size = copiable_size;
}