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
typedef  int /*<<< orphan*/  AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_relid ; 
 int /*<<< orphan*/  child_reltype ; 
 int /*<<< orphan*/  parent_relid ; 
 int /*<<< orphan*/  parent_reloid ; 
 int /*<<< orphan*/  parent_reltype ; 
 int /*<<< orphan*/  translated_vars ; 

__attribute__((used)) static void
_outAppendRelInfo(StringInfo str, const AppendRelInfo *node)
{
	WRITE_NODE_TYPE("APPENDRELINFO");

	WRITE_UINT_FIELD(parent_relid);
	WRITE_UINT_FIELD(child_relid);
	WRITE_OID_FIELD(parent_reltype);
	WRITE_OID_FIELD(child_reltype);
	WRITE_NODE_FIELD(translated_vars);
	WRITE_OID_FIELD(parent_reloid);
}