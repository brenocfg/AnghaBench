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
 int get_16 (unsigned char const*) ; 

__attribute__((used)) static int configure_function(const unsigned char *buf, int *more) 
{
	/* the init field seems to be a two-byte field
	 * which is non-zero if there are an other function following
	 * I think it is the length of the function def 
	 */
	*more = get_16(buf);
	
	return 2;
}