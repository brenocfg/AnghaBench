#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_5__ {TYPE_1__* rd_rel; int /*<<< orphan*/  rd_backend; int /*<<< orphan*/  rd_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  reltoastrelid; } ;
typedef  TYPE_2__* Relation ;
typedef  scalar_t__ ForkNumber ;

/* Variables and functions */
 scalar_t__ MAX_FORKNUM ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ calculate_relation_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ calculate_toast_table_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
calculate_table_size(Relation rel)
{
	int64		size = 0;
	ForkNumber	forkNum;

	/*
	 * heap size, including FSM and VM
	 */
	for (forkNum = 0; forkNum <= MAX_FORKNUM; forkNum++)
		size += calculate_relation_size(&(rel->rd_node), rel->rd_backend,
										forkNum);

	/*
	 * Size of toast relation
	 */
	if (OidIsValid(rel->rd_rel->reltoastrelid))
		size += calculate_toast_table_size(rel->rd_rel->reltoastrelid);

	return size;
}