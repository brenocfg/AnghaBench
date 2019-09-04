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
struct pgid {int dummy; } ;

/* Variables and functions */
 int memcmp (char*,char*,int) ; 

__attribute__((used)) static int pgid_cmp(struct pgid *p1, struct pgid *p2)
{
	return memcmp((char *) p1 + 1, (char *) p2 + 1,
		      sizeof(struct pgid) - 1);
}