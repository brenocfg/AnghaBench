#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t whichhost; char* pgpass; TYPE_1__* connhost; } ;
struct TYPE_4__ {char* password; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */

char *
PQpass(const PGconn *conn)
{
	char	   *password = NULL;

	if (!conn)
		return NULL;
	if (conn->connhost != NULL)
		password = conn->connhost[conn->whichhost].password;
	if (password == NULL)
		password = conn->pgpass;
	/* Historically we've returned "" not NULL for no password specified */
	if (password == NULL)
		password = "";
	return password;
}