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
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  GatherMergePath ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  _outPathInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  num_workers ; 
 int /*<<< orphan*/  subpath ; 

__attribute__((used)) static void
_outGatherMergePath(StringInfo str, const GatherMergePath *node)
{
	WRITE_NODE_TYPE("GATHERMERGEPATH");

	_outPathInfo(str, (const Path *) node);

	WRITE_NODE_FIELD(subpath);
	WRITE_INT_FIELD(num_workers);
}