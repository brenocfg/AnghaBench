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
struct nsinfo {int dummy; } ;

/* Variables and functions */
 int copyfile_mode_ns (char const*,char const*,int,struct nsinfo*) ; 

int copyfile_ns(const char *from, const char *to, struct nsinfo *nsi)
{
	return copyfile_mode_ns(from, to, 0755, nsi);
}