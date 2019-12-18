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
struct connection {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  PGTransactionStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  PQTRANS_UNKNOWN ; 
 int /*<<< orphan*/  PQtransactionStatus (int /*<<< orphan*/ ) ; 
 struct connection* ecpg_get_connection (char const*) ; 

PGTransactionStatusType
ECPGtransactionStatus(const char *connection_name)
{
	const struct connection *con;

	con = ecpg_get_connection(connection_name);
	if (con == NULL)
	{
		/* transaction status is unknown */
		return PQTRANS_UNKNOWN;
	}

	return PQtransactionStatus(con->connection);

}