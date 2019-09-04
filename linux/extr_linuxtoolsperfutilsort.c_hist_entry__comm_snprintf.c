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
struct hist_entry {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm__str (int /*<<< orphan*/ ) ; 
 int repsep_snprintf (char*,size_t,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_entry__comm_snprintf(struct hist_entry *he, char *bf,
				     size_t size, unsigned int width)
{
	return repsep_snprintf(bf, size, "%-*.*s", width, width, comm__str(he->comm));
}