#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sign; scalar_t__ allistrue; } ;
typedef  TYPE_1__ CACHESIGN ;

/* Variables and functions */
 int SIGLENBIT ; 
 int hemdistsign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sizebitvec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hemdistcache(CACHESIGN *a, CACHESIGN *b)
{
	if (a->allistrue)
	{
		if (b->allistrue)
			return 0;
		else
			return SIGLENBIT - sizebitvec(b->sign);
	}
	else if (b->allistrue)
		return SIGLENBIT - sizebitvec(a->sign);

	return hemdistsign(a->sign, b->sign);
}