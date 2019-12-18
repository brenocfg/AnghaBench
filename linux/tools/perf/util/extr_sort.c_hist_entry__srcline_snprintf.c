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
struct hist_entry {scalar_t__ srcline; } ;

/* Variables and functions */
 scalar_t__ hist_entry__srcline (struct hist_entry*) ; 
 int repsep_snprintf (char*,size_t,char*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int hist_entry__srcline_snprintf(struct hist_entry *he, char *bf,
					size_t size, unsigned int width)
{
	if (!he->srcline)
		he->srcline = hist_entry__srcline(he);

	return repsep_snprintf(bf, size, "%-.*s", width, he->srcline);
}