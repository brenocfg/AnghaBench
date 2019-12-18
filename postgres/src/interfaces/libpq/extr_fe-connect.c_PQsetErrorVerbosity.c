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
struct TYPE_3__ {int /*<<< orphan*/  verbosity; } ;
typedef  TYPE_1__ PGconn ;
typedef  int /*<<< orphan*/  PGVerbosity ;

/* Variables and functions */
 int /*<<< orphan*/  PQERRORS_DEFAULT ; 

PGVerbosity
PQsetErrorVerbosity(PGconn *conn, PGVerbosity verbosity)
{
	PGVerbosity old;

	if (!conn)
		return PQERRORS_DEFAULT;
	old = conn->verbosity;
	conn->verbosity = verbosity;
	return old;
}