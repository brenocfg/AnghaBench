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
typedef  int /*<<< orphan*/  PartitionRangeDatum ;

/* Variables and functions */
 int /*<<< orphan*/  PartitionRangeDatumKind ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  value ; 

__attribute__((used)) static void
_outPartitionRangeDatum(StringInfo str, const PartitionRangeDatum *node)
{
	WRITE_NODE_TYPE("PARTITIONRANGEDATUM");

	WRITE_ENUM_FIELD(kind, PartitionRangeDatumKind);
	WRITE_NODE_FIELD(value);
	WRITE_LOCATION_FIELD(location);
}