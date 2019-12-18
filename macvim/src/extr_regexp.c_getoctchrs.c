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

/* Variables and functions */
 int hex2nr (int) ; 
 int* regparse ; 

__attribute__((used)) static int
getoctchrs()
{
    int		nr = 0;
    int		c;
    int		i;

    for (i = 0; i < 3 && nr < 040; ++i)
    {
	c = regparse[0];
	if (c < '0' || c > '7')
	    break;
	nr <<= 3;
	nr |= hex2nr(c);
	++regparse;
    }

    if (i == 0)
	return -1;
    return nr;
}