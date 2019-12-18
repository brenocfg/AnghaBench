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
struct treepath {scalar_t__ path_length; } ;

/* Variables and functions */
 scalar_t__ ILLEGAL_PATH_ELEMENT_OFFSET ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 

int reiserfs_check_path(struct treepath *p)
{
	RFALSE(p->path_length != ILLEGAL_PATH_ELEMENT_OFFSET,
	       "path not properly relsed");
	return 0;
}