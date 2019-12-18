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
typedef  int /*<<< orphan*/  Scan ;
typedef  int /*<<< orphan*/  BitmapIndexScan ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outScanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  indexid ; 
 int /*<<< orphan*/  indexqual ; 
 int /*<<< orphan*/  indexqualorig ; 
 int /*<<< orphan*/  isshared ; 

__attribute__((used)) static void
_outBitmapIndexScan(StringInfo str, const BitmapIndexScan *node)
{
	WRITE_NODE_TYPE("BITMAPINDEXSCAN");

	_outScanInfo(str, (const Scan *) node);

	WRITE_OID_FIELD(indexid);
	WRITE_BOOL_FIELD(isshared);
	WRITE_NODE_FIELD(indexqual);
	WRITE_NODE_FIELD(indexqualorig);
}