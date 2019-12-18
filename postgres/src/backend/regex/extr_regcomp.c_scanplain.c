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
struct vars {int /*<<< orphan*/ * now; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  CCLASS ; 
 int /*<<< orphan*/  COLLEL ; 
 int /*<<< orphan*/  ECLASS ; 
 int /*<<< orphan*/  END ; 
 scalar_t__ ISERR () ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  PLAIN ; 
 scalar_t__ SEE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static const chr *				/* just after end of sequence */
scanplain(struct vars *v)
{
	const chr  *endp;

	assert(SEE(COLLEL) || SEE(ECLASS) || SEE(CCLASS));
	NEXT();

	endp = v->now;
	while (SEE(PLAIN))
	{
		endp = v->now;
		NEXT();
	}

	assert(SEE(END) || ISERR());
	NEXT();

	return endp;
}