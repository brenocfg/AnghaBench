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
struct TYPE_3__ {int /*<<< orphan*/  show_context; } ;
typedef  TYPE_1__ PGconn ;
typedef  int /*<<< orphan*/  PGContextVisibility ;

/* Variables and functions */
 int /*<<< orphan*/  PQSHOW_CONTEXT_ERRORS ; 

PGContextVisibility
PQsetErrorContextVisibility(PGconn *conn, PGContextVisibility show_context)
{
	PGContextVisibility old;

	if (!conn)
		return PQSHOW_CONTEXT_ERRORS;
	old = conn->show_context;
	conn->show_context = show_context;
	return old;
}