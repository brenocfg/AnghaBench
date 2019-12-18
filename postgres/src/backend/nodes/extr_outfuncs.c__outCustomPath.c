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
struct TYPE_5__ {TYPE_1__* methods; } ;
struct TYPE_4__ {int /*<<< orphan*/  CustomName; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  TYPE_2__ CustomPath ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPathInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  custom_paths ; 
 int /*<<< orphan*/  custom_private ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  outToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_outCustomPath(StringInfo str, const CustomPath *node)
{
	WRITE_NODE_TYPE("CUSTOMPATH");

	_outPathInfo(str, (const Path *) node);

	WRITE_UINT_FIELD(flags);
	WRITE_NODE_FIELD(custom_paths);
	WRITE_NODE_FIELD(custom_private);
	appendStringInfoString(str, " :methods ");
	outToken(str, node->methods->CustomName);
}