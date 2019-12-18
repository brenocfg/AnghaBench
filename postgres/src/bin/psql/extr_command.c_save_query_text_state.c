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
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  ConditionalStack ;

/* Variables and functions */
 int /*<<< orphan*/  conditional_stack_set_paren_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conditional_stack_set_query_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psql_scan_get_paren_depth (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
save_query_text_state(PsqlScanState scan_state, ConditionalStack cstack,
					  PQExpBuffer query_buf)
{
	if (query_buf)
		conditional_stack_set_query_len(cstack, query_buf->len);
	conditional_stack_set_paren_depth(cstack,
									  psql_scan_get_paren_depth(scan_state));
}