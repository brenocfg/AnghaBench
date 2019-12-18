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
struct TYPE_3__ {char* label; } ;
typedef  TYPE_1__ pending_label ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* client_label_committed ; 
 char* client_label_func ; 
 char* client_label_peer ; 
 scalar_t__ client_label_pending ; 
 TYPE_1__* llast (scalar_t__) ; 

char *
sepgsql_get_client_label(void)
{
	/* trusted procedure client label override */
	if (client_label_func)
		return client_label_func;

	/* uncommitted sepgsql_setcon() value */
	if (client_label_pending)
	{
		pending_label *plabel = llast(client_label_pending);

		if (plabel->label)
			return plabel->label;
	}
	else if (client_label_committed)
		return client_label_committed;	/* set by sepgsql_setcon() committed */

	/* default label */
	Assert(client_label_peer != NULL);
	return client_label_peer;
}