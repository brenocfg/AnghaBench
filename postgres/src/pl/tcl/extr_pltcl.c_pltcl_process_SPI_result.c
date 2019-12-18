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
typedef  size_t uint64 ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_4__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ SPITupleTable ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
#define  SPI_OK_DELETE 137 
#define  SPI_OK_DELETE_RETURNING 136 
#define  SPI_OK_INSERT 135 
#define  SPI_OK_INSERT_RETURNING 134 
#define  SPI_OK_REWRITTEN 133 
#define  SPI_OK_SELECT 132 
#define  SPI_OK_SELINTO 131 
#define  SPI_OK_UPDATE 130 
#define  SPI_OK_UPDATE_RETURNING 129 
#define  SPI_OK_UTILITY 128 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_1__*) ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 int TCL_BREAK ; 
 int TCL_CONTINUE ; 
 int TCL_ERROR ; 
 int TCL_OK ; 
 int TCL_RETURN ; 
 int /*<<< orphan*/  Tcl_AppendResult (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewIntObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewWideIntObj (size_t) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pltcl_set_tuple_values (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pltcl_process_SPI_result(Tcl_Interp *interp,
						 const char *arrayname,
						 Tcl_Obj *loop_body,
						 int spi_rc,
						 SPITupleTable *tuptable,
						 uint64 ntuples)
{
	int			my_rc = TCL_OK;
	int			loop_rc;
	HeapTuple  *tuples;
	TupleDesc	tupdesc;

	switch (spi_rc)
	{
		case SPI_OK_SELINTO:
		case SPI_OK_INSERT:
		case SPI_OK_DELETE:
		case SPI_OK_UPDATE:
			Tcl_SetObjResult(interp, Tcl_NewWideIntObj(ntuples));
			break;

		case SPI_OK_UTILITY:
		case SPI_OK_REWRITTEN:
			if (tuptable == NULL)
			{
				Tcl_SetObjResult(interp, Tcl_NewIntObj(0));
				break;
			}
			/* fall through for utility returning tuples */
			/* FALLTHROUGH */

		case SPI_OK_SELECT:
		case SPI_OK_INSERT_RETURNING:
		case SPI_OK_DELETE_RETURNING:
		case SPI_OK_UPDATE_RETURNING:

			/*
			 * Process the tuples we got
			 */
			tuples = tuptable->vals;
			tupdesc = tuptable->tupdesc;

			if (loop_body == NULL)
			{
				/*
				 * If there is no loop body given, just set the variables from
				 * the first tuple (if any)
				 */
				if (ntuples > 0)
					pltcl_set_tuple_values(interp, arrayname, 0,
										   tuples[0], tupdesc);
			}
			else
			{
				/*
				 * There is a loop body - process all tuples and evaluate the
				 * body on each
				 */
				uint64		i;

				for (i = 0; i < ntuples; i++)
				{
					pltcl_set_tuple_values(interp, arrayname, i,
										   tuples[i], tupdesc);

					loop_rc = Tcl_EvalObjEx(interp, loop_body, 0);

					if (loop_rc == TCL_OK)
						continue;
					if (loop_rc == TCL_CONTINUE)
						continue;
					if (loop_rc == TCL_RETURN)
					{
						my_rc = TCL_RETURN;
						break;
					}
					if (loop_rc == TCL_BREAK)
						break;
					my_rc = TCL_ERROR;
					break;
				}
			}

			if (my_rc == TCL_OK)
			{
				Tcl_SetObjResult(interp, Tcl_NewWideIntObj(ntuples));
			}
			break;

		default:
			Tcl_AppendResult(interp, "pltcl: SPI_execute failed: ",
							 SPI_result_code_string(spi_rc), NULL);
			my_rc = TCL_ERROR;
			break;
	}

	SPI_freetuptable(tuptable);

	return my_rc;
}