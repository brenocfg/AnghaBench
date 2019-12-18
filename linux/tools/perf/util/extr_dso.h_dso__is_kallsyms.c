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
struct dso {char* long_name; scalar_t__ kernel; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dso__is_kallsyms(struct dso *dso)
{
	return dso->kernel && dso->long_name[0] != '/';
}