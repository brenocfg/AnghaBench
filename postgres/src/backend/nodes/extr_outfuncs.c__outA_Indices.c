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
typedef  int /*<<< orphan*/  A_Indices ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  is_slice ; 
 int /*<<< orphan*/  lidx ; 
 int /*<<< orphan*/  uidx ; 

__attribute__((used)) static void
_outA_Indices(StringInfo str, const A_Indices *node)
{
	WRITE_NODE_TYPE("A_INDICES");

	WRITE_BOOL_FIELD(is_slice);
	WRITE_NODE_FIELD(lidx);
	WRITE_NODE_FIELD(uidx);
}