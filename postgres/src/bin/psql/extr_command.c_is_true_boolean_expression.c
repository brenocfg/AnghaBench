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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int ParseVariableBool (int /*<<< orphan*/ ,char const*,int*) ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 TYPE_1__* gather_boolean_expression (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_true_boolean_expression(PsqlScanState scan_state, const char *name)
{
	PQExpBuffer buf = gather_boolean_expression(scan_state);
	bool		value = false;
	bool		success = ParseVariableBool(buf->data, name, &value);

	destroyPQExpBuffer(buf);
	return success && value;
}