#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_GSS_CODE ; 
 int /*<<< orphan*/  GSS_C_MECH_CODE ; 
 int /*<<< orphan*/  pg_GSS_error_int (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

void
pg_GSS_error(const char *mprefix, PGconn *conn,
			 OM_uint32 maj_stat, OM_uint32 min_stat)
{
	resetPQExpBuffer(&conn->errorMessage);

	/* Fetch major error codes */
	pg_GSS_error_int(&conn->errorMessage, mprefix, maj_stat, GSS_C_GSS_CODE);

	/* Add the minor codes as well */
	pg_GSS_error_int(&conn->errorMessage, mprefix, min_stat, GSS_C_MECH_CODE);
}