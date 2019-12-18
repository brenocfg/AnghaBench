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
typedef  int /*<<< orphan*/  ltree_gist ;

/* Variables and functions */
 int ASIGLENBIT ; 
 scalar_t__ LTG_ISALLTRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTG_SIGN (int /*<<< orphan*/ *) ; 
 int hemdistsign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sizebitvec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hemdist(ltree_gist *a, ltree_gist *b)
{
	if (LTG_ISALLTRUE(a))
	{
		if (LTG_ISALLTRUE(b))
			return 0;
		else
			return ASIGLENBIT - sizebitvec(LTG_SIGN(b));
	}
	else if (LTG_ISALLTRUE(b))
		return ASIGLENBIT - sizebitvec(LTG_SIGN(a));

	return hemdistsign(LTG_SIGN(a), LTG_SIGN(b));
}