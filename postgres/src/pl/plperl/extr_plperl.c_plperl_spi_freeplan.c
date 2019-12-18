#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* query_data; } ;
typedef  TYPE_1__ plperl_query_entry ;
struct TYPE_6__ {int /*<<< orphan*/  plan_cxt; int /*<<< orphan*/  plan; } ;
typedef  TYPE_2__ plperl_query_desc ;
struct TYPE_7__ {int /*<<< orphan*/  query_hash; } ;
typedef  int /*<<< orphan*/  SPIPlanPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_freeplan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_spi_usage_allowed () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* plperl_active_interp ; 

void
plperl_spi_freeplan(char *query)
{
	SPIPlanPtr	plan;
	plperl_query_desc *qdesc;
	plperl_query_entry *hash_entry;

	check_spi_usage_allowed();

	hash_entry = hash_search(plperl_active_interp->query_hash, query,
							 HASH_FIND, NULL);
	if (hash_entry == NULL)
		elog(ERROR, "spi_freeplan: Invalid prepared query passed");

	qdesc = hash_entry->query_data;
	if (qdesc == NULL)
		elog(ERROR, "spi_freeplan: plperl query_hash value vanished");
	plan = qdesc->plan;

	/*
	 * free all memory before SPI_freeplan, so if it dies, nothing will be
	 * left over
	 */
	hash_search(plperl_active_interp->query_hash, query,
				HASH_REMOVE, NULL);

	MemoryContextDelete(qdesc->plan_cxt);

	SPI_freeplan(plan);
}