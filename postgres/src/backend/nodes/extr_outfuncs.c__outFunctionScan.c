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
typedef  int /*<<< orphan*/  FunctionScan ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  _outScanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  funcordinality ; 
 int /*<<< orphan*/  functions ; 

__attribute__((used)) static void
_outFunctionScan(StringInfo str, const FunctionScan *node)
{
	WRITE_NODE_TYPE("FUNCTIONSCAN");

	_outScanInfo(str, (const Scan *) node);

	WRITE_NODE_FIELD(functions);
	WRITE_BOOL_FIELD(funcordinality);
}