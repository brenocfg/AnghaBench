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
typedef  scalar_t__ uint ;
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int BUDMIN ; 
 char* budtab ; 
 int max (char,char) ; 

__attribute__((used)) static int dbMaxBud(u8 * cp)
{
	signed char tmp1, tmp2;

	/* check if the wmap word is all free. if so, the
	 * free buddy size is BUDMIN.
	 */
	if (*((uint *) cp) == 0)
		return (BUDMIN);

	/* check if the wmap word is half free. if so, the
	 * free buddy size is BUDMIN-1.
	 */
	if (*((u16 *) cp) == 0 || *((u16 *) cp + 1) == 0)
		return (BUDMIN - 1);

	/* not all free or half free. determine the free buddy
	 * size thru table lookup using quarters of the wmap word.
	 */
	tmp1 = max(budtab[cp[2]], budtab[cp[3]]);
	tmp2 = max(budtab[cp[0]], budtab[cp[1]]);
	return (max(tmp1, tmp2));
}