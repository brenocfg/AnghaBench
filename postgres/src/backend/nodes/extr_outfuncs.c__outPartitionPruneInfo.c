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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  PartitionPruneInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  other_subplans ; 
 int /*<<< orphan*/  prune_infos ; 

__attribute__((used)) static void
_outPartitionPruneInfo(StringInfo str, const PartitionPruneInfo *node)
{
	WRITE_NODE_TYPE("PARTITIONPRUNEINFO");

	WRITE_NODE_FIELD(prune_infos);
	WRITE_BITMAPSET_FIELD(other_subplans);
}