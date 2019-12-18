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
typedef  int /*<<< orphan*/  AccessPriv ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cols ; 
 int /*<<< orphan*/  priv_name ; 

__attribute__((used)) static bool
_equalAccessPriv(const AccessPriv *a, const AccessPriv *b)
{
	COMPARE_STRING_FIELD(priv_name);
	COMPARE_NODE_FIELD(cols);

	return true;
}