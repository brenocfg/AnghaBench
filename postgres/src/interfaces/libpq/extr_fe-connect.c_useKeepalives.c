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
struct TYPE_3__ {int /*<<< orphan*/ * keepalives; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int strtol (int /*<<< orphan*/ *,char**,int) ; 

__attribute__((used)) static int
useKeepalives(PGconn *conn)
{
	char	   *ep;
	int			val;

	if (conn->keepalives == NULL)
		return 1;
	val = strtol(conn->keepalives, &ep, 10);
	if (*ep)
		return -1;
	return val != 0 ? 1 : 0;
}