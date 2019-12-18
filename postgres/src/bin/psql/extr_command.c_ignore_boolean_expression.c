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
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  destroyPQExpBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gather_boolean_expression (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ignore_boolean_expression(PsqlScanState scan_state)
{
	PQExpBuffer buf = gather_boolean_expression(scan_state);

	destroyPQExpBuffer(buf);
}