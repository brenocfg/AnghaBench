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
struct TYPE_4__ {scalar_t__ interp; } ;
typedef  TYPE_1__ plperl_interp_desc ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/  activate_interpreter (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plperl_destroy_interp (scalar_t__*) ; 
 int plperl_ending ; 
 scalar_t__ plperl_held_interp ; 
 int /*<<< orphan*/  plperl_interp_hash ; 

__attribute__((used)) static void
plperl_fini(int code, Datum arg)
{
	HASH_SEQ_STATUS hash_seq;
	plperl_interp_desc *interp_desc;

	elog(DEBUG3, "plperl_fini");

	/*
	 * Indicate that perl is terminating. Disables use of spi_* functions when
	 * running END/DESTROY code. See check_spi_usage_allowed(). Could be
	 * enabled in future, with care, using a transaction
	 * http://archives.postgresql.org/pgsql-hackers/2010-01/msg02743.php
	 */
	plperl_ending = true;

	/* Only perform perl cleanup if we're exiting cleanly */
	if (code)
	{
		elog(DEBUG3, "plperl_fini: skipped");
		return;
	}

	/* Zap the "held" interpreter, if we still have it */
	plperl_destroy_interp(&plperl_held_interp);

	/* Zap any fully-initialized interpreters */
	hash_seq_init(&hash_seq, plperl_interp_hash);
	while ((interp_desc = hash_seq_search(&hash_seq)) != NULL)
	{
		if (interp_desc->interp)
		{
			activate_interpreter(interp_desc);
			plperl_destroy_interp(&interp_desc->interp);
		}
	}

	elog(DEBUG3, "plperl_fini: done");
}