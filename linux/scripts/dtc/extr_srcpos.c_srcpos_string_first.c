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
struct srcpos {int dummy; } ;

/* Variables and functions */
 char* srcpos_string_comment (struct srcpos*,int,int) ; 

char *srcpos_string_first(struct srcpos *pos, int level)
{
	return srcpos_string_comment(pos, true, level);
}