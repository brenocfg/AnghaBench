#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int e_shnum; } ;
struct TYPE_8__ {TYPE_2__* sections; TYPE_1__ header; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ MyElf_Section ;
typedef  TYPE_3__ MyElf_File ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

MyElf_Section* GetElfSection(MyElf_File *elf, char *name) {

	int i;

    for(i = 0; i < elf->header.e_shnum - 1; i++) {
		if(!strcmp(name, elf->sections[i].name)) {
			debug("Found section '%s'.\r\n", name);
			return &elf->sections[i];
		}
	}

	debug("Could not find section '%s'.\r\n", name);
	return 0;
}