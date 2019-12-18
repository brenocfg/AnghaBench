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
struct vars {int cflags; int /*<<< orphan*/  nexttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY ; 
 int /*<<< orphan*/  INTOCON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L_BRE ; 
 int /*<<< orphan*/  L_ERE ; 
 int /*<<< orphan*/  L_Q ; 
 int /*<<< orphan*/  NOERR () ; 
 int REG_ADVANCED ; 
 int REG_ADVF ; 
 int REG_EXPANDED ; 
 int REG_EXTENDED ; 
 int REG_NEWLINE ; 
 int REG_QUOTE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  next (struct vars*) ; 
 int /*<<< orphan*/  prefixes (struct vars*) ; 

__attribute__((used)) static void
lexstart(struct vars *v)
{
	prefixes(v);				/* may turn on new type bits etc. */
	NOERR();

	if (v->cflags & REG_QUOTE)
	{
		assert(!(v->cflags & (REG_ADVANCED | REG_EXPANDED | REG_NEWLINE)));
		INTOCON(L_Q);
	}
	else if (v->cflags & REG_EXTENDED)
	{
		assert(!(v->cflags & REG_QUOTE));
		INTOCON(L_ERE);
	}
	else
	{
		assert(!(v->cflags & (REG_QUOTE | REG_ADVF)));
		INTOCON(L_BRE);
	}

	v->nexttype = EMPTY;		/* remember we were at the start */
	next(v);					/* set up the first token */
}