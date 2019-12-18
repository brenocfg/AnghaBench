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
typedef  int /*<<< orphan*/  ltxtquery ;
typedef  int /*<<< orphan*/  ltree_gist ;

/* Variables and functions */
 int /*<<< orphan*/  GETQUERY (int /*<<< orphan*/ *) ; 
 scalar_t__ LTG_ISALLTRUE (int /*<<< orphan*/ *) ; 
 scalar_t__ LTG_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkcondition_bit ; 
 int ltree_execute (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
gist_qtxt(ltree_gist *key, ltxtquery *query)
{
	if (LTG_ISALLTRUE(key))
		return true;

	return ltree_execute(
						 GETQUERY(query),
						 (void *) LTG_SIGN(key), false,
						 checkcondition_bit
		);
}