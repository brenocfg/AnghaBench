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
typedef  int /*<<< orphan*/  PLpgSQL_datum ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int datums_alloc ; 
 scalar_t__ datums_last ; 
 int /*<<< orphan*/  plpgsql_Datums ; 
 int /*<<< orphan*/  plpgsql_compile_tmp_cxt ; 
 scalar_t__ plpgsql_nDatums ; 

__attribute__((used)) static void
plpgsql_start_datums(void)
{
	datums_alloc = 128;
	plpgsql_nDatums = 0;
	/* This is short-lived, so needn't allocate in function's cxt */
	plpgsql_Datums = MemoryContextAlloc(plpgsql_compile_tmp_cxt,
										sizeof(PLpgSQL_datum *) * datums_alloc);
	/* datums_last tracks what's been seen by plpgsql_add_initdatums() */
	datums_last = 0;
}