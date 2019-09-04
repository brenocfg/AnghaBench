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
struct strfilter {int dummy; } ;

/* Variables and functions */
 int strfilter__append (struct strfilter*,int,char const*,char const**) ; 

int strfilter__and(struct strfilter *filter, const char *rules,
		   const char **err)
{
	return strfilter__append(filter, false, rules, err);
}