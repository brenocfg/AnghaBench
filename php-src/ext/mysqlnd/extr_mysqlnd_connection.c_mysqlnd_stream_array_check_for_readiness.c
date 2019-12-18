#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum mysqlnd_connection_state { ____Placeholder_mysqlnd_connection_state } mysqlnd_connection_state ;
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ MYSQLND ;

/* Variables and functions */
 int const CONN_QUIT_SENT ; 
 int const CONN_READY ; 
 int GET_CONNECTION_STATE (int /*<<< orphan*/ *) ; 
 TYPE_2__** ecalloc (unsigned int,int) ; 

MYSQLND **
mysqlnd_stream_array_check_for_readiness(MYSQLND ** conn_array)
{
	unsigned int cnt = 0;
	MYSQLND **p = conn_array, **p_p;
	MYSQLND **ret = NULL;

	while (*p) {
		const enum mysqlnd_connection_state conn_state = GET_CONNECTION_STATE(&((*p)->data->state));
		if (conn_state <= CONN_READY || conn_state == CONN_QUIT_SENT) {
			cnt++;
		}
		p++;
	}
	if (cnt) {
		MYSQLND **ret_p = ret = ecalloc(cnt + 1, sizeof(MYSQLND *));
		p_p = p = conn_array;
		while (*p) {
			const enum mysqlnd_connection_state conn_state = GET_CONNECTION_STATE(&((*p)->data->state));
			if (conn_state <= CONN_READY || conn_state == CONN_QUIT_SENT) {
				*ret_p = *p;
				*p = NULL;
				ret_p++;
			} else {
				*p_p = *p;
				p_p++;
			}
			p++;
		}
		*ret_p = NULL;
	}
	return ret;
}