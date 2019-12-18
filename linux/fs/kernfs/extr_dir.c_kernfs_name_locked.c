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
struct kernfs_node {char* name; scalar_t__ parent; } ;

/* Variables and functions */
 int strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int kernfs_name_locked(struct kernfs_node *kn, char *buf, size_t buflen)
{
	if (!kn)
		return strlcpy(buf, "(null)", buflen);

	return strlcpy(buf, kn->parent ? kn->name : "/", buflen);
}