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
struct vimoption {int flags; int /*<<< orphan*/ ** def_val; scalar_t__ var; int /*<<< orphan*/ * fullname; } ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int P_ALLOCED ; 
 int P_DEF_ALLOCED ; 
 size_t VI_DEFAULT ; 
 int /*<<< orphan*/  clear_termcodes () ; 
 void* empty_option ; 
 int /*<<< orphan*/  free_string_option (int /*<<< orphan*/ *) ; 
 scalar_t__ istermoption (struct vimoption*) ; 
 struct vimoption* options ; 

void
free_termoptions()
{
    struct vimoption   *p;

    for (p = &options[0]; p->fullname != NULL; p++)
	if (istermoption(p))
	{
	    if (p->flags & P_ALLOCED)
		free_string_option(*(char_u **)(p->var));
	    if (p->flags & P_DEF_ALLOCED)
		free_string_option(p->def_val[VI_DEFAULT]);
	    *(char_u **)(p->var) = empty_option;
	    p->def_val[VI_DEFAULT] = empty_option;
	    p->flags &= ~(P_ALLOCED|P_DEF_ALLOCED);
	}
    clear_termcodes();
}