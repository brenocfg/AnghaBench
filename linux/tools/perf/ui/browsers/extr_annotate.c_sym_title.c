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
struct symbol {char* name; } ;
struct map {TYPE_1__* dso; } ;
struct TYPE_2__ {char* long_name; } ;

/* Variables and functions */
 char* percent_type_str (int) ; 
 int snprintf (char*,size_t,char*,char*,char*,char*) ; 

__attribute__((used)) static int sym_title(struct symbol *sym, struct map *map, char *title,
		     size_t sz, int percent_type)
{
	return snprintf(title, sz, "%s  %s [Percent: %s]", sym->name, map->dso->long_name,
			percent_type_str(percent_type));
}