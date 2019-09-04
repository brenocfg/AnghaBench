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
struct proc_dir_entry {unsigned int namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int memcmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int proc_match(const char *name, struct proc_dir_entry *de, unsigned int len)
{
	if (len < de->namelen)
		return -1;
	if (len > de->namelen)
		return 1;

	return memcmp(name, de->name, len);
}