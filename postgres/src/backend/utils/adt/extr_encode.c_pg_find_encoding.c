#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pg_encoding {int dummy; } ;
struct TYPE_2__ {struct pg_encoding const enc; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* enclist ; 
 scalar_t__ pg_strcasecmp (scalar_t__,char const*) ; 

__attribute__((used)) static const struct pg_encoding *
pg_find_encoding(const char *name)
{
	int			i;

	for (i = 0; enclist[i].name; i++)
		if (pg_strcasecmp(enclist[i].name, name) == 0)
			return &enclist[i].enc;

	return NULL;
}