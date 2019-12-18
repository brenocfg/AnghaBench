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
struct vars {int nextvalue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGIT ; 
 int DUPMAX ; 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  REG_BADBR ; 
 scalar_t__ SEE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int						/* value, <= DUPMAX */
scannum(struct vars *v)
{
	int			n = 0;

	while (SEE(DIGIT) && n < DUPMAX)
	{
		n = n * 10 + v->nextvalue;
		NEXT();
	}
	if (SEE(DIGIT) || n > DUPMAX)
	{
		ERR(REG_BADBR);
		return 0;
	}
	return n;
}