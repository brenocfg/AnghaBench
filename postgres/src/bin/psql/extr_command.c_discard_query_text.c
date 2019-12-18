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
struct TYPE_3__ {int len; char* data; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  ConditionalStack ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  conditional_stack_get_paren_depth (int /*<<< orphan*/ ) ; 
 int conditional_stack_get_query_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psql_scan_set_paren_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
discard_query_text(PsqlScanState scan_state, ConditionalStack cstack,
				   PQExpBuffer query_buf)
{
	if (query_buf)
	{
		int			new_len = conditional_stack_get_query_len(cstack);

		Assert(new_len >= 0 && new_len <= query_buf->len);
		query_buf->len = new_len;
		query_buf->data[new_len] = '\0';
	}
	psql_scan_set_paren_depth(scan_state,
							  conditional_stack_get_paren_depth(cstack));
}