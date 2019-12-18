#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* sections; struct TYPE_4__* strings; scalar_t__ fd; } ;
typedef  TYPE_1__ MyElf_File ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void UnloadElf(MyElf_File *elf) {
	if (elf) {
		debug("Unloading elf file.\r\n");
		if(elf->fd) fclose(elf->fd);
		if(elf->strings) free(elf->strings);
		if(elf->sections) free(elf->sections);
		free(elf);
	}
}