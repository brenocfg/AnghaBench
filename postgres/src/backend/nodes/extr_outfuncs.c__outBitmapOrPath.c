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
typedef  int /*<<< orphan*/  BitmapOrPath ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  _outPathInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bitmapquals ; 
 int /*<<< orphan*/  bitmapselectivity ; 

__attribute__((used)) static void
_outBitmapOrPath(StringInfo str, const BitmapOrPath *node)
{
	WRITE_NODE_TYPE("BITMAPORPATH");

	_outPathInfo(str, (const Path *) node);

	WRITE_NODE_FIELD(bitmapquals);
	WRITE_FLOAT_FIELD(bitmapselectivity, "%.4f");
}