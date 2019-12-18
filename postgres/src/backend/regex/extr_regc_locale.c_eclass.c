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
struct vars {int cflags; } ;
struct cvec {int dummy; } ;
typedef  char chr ;

/* Variables and functions */
 char CHR (char) ; 
 int REG_FAKE ; 
 int /*<<< orphan*/  addchr (struct cvec*,char) ; 
 struct cvec* allcases (struct vars*,char) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct cvec* getcvec (struct vars*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cvec *
eclass(struct vars *v,			/* context */
	   chr c,					/* Collating element representing the
								 * equivalence class. */
	   int cases)				/* all cases? */
{
	struct cvec *cv;

	/* crude fake equivalence class for testing */
	if ((v->cflags & REG_FAKE) && c == 'x')
	{
		cv = getcvec(v, 4, 0);
		addchr(cv, CHR('x'));
		addchr(cv, CHR('y'));
		if (cases)
		{
			addchr(cv, CHR('X'));
			addchr(cv, CHR('Y'));
		}
		return cv;
	}

	/* otherwise, none */
	if (cases)
		return allcases(v, c);
	cv = getcvec(v, 1, 0);
	assert(cv != NULL);
	addchr(cv, c);
	return cv;
}