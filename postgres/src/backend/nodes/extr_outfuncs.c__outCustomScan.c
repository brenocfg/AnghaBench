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
typedef  int /*<<< orphan*/  Scan ;
typedef  TYPE_2__ CustomScan ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outScanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  custom_exprs ; 
 int /*<<< orphan*/  custom_plans ; 
 int /*<<< orphan*/  custom_private ; 
 int /*<<< orphan*/  custom_relids ; 
 int /*<<< orphan*/  custom_scan_tlist ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  outToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_outCustomScan(StringInfo str, const CustomScan *node)
{
	WRITE_NODE_TYPE("CUSTOMSCAN");

	_outScanInfo(str, (const Scan *) node);

	WRITE_UINT_FIELD(flags);
	WRITE_NODE_FIELD(custom_plans);
	WRITE_NODE_FIELD(custom_exprs);
	WRITE_NODE_FIELD(custom_private);
	WRITE_NODE_FIELD(custom_scan_tlist);
	WRITE_BITMAPSET_FIELD(custom_relids);
	/* CustomName is a key to lookup CustomScanMethods */
	appendStringInfoString(str, " :methods ");
	outToken(str, node->methods->CustomName);
}