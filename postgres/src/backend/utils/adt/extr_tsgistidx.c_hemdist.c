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
typedef  int /*<<< orphan*/  SignTSVector ;

/* Variables and functions */
 int /*<<< orphan*/  GETSIGN (int /*<<< orphan*/ *) ; 
 scalar_t__ ISALLTRUE (int /*<<< orphan*/ *) ; 
 int SIGLENBIT ; 
 int hemdistsign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sizebitvec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hemdist(SignTSVector *a, SignTSVector *b)
{
	if (ISALLTRUE(a))
	{
		if (ISALLTRUE(b))
			return 0;
		else
			return SIGLENBIT - sizebitvec(GETSIGN(b));
	}
	else if (ISALLTRUE(b))
		return SIGLENBIT - sizebitvec(GETSIGN(a));

	return hemdistsign(GETSIGN(a), GETSIGN(b));
}