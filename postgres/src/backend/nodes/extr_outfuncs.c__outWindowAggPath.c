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
typedef  int /*<<< orphan*/  WindowAggPath ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  _outPathInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  subpath ; 
 int /*<<< orphan*/  winclause ; 

__attribute__((used)) static void
_outWindowAggPath(StringInfo str, const WindowAggPath *node)
{
	WRITE_NODE_TYPE("WINDOWAGGPATH");

	_outPathInfo(str, (const Path *) node);

	WRITE_NODE_FIELD(subpath);
	WRITE_NODE_FIELD(winclause);
}