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
typedef  int /*<<< orphan*/  PlaceHolderVar ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phexpr ; 
 int /*<<< orphan*/  phid ; 
 int /*<<< orphan*/  phlevelsup ; 
 int /*<<< orphan*/  phrels ; 

__attribute__((used)) static void
_outPlaceHolderVar(StringInfo str, const PlaceHolderVar *node)
{
	WRITE_NODE_TYPE("PLACEHOLDERVAR");

	WRITE_NODE_FIELD(phexpr);
	WRITE_BITMAPSET_FIELD(phrels);
	WRITE_UINT_FIELD(phid);
	WRITE_UINT_FIELD(phlevelsup);
}