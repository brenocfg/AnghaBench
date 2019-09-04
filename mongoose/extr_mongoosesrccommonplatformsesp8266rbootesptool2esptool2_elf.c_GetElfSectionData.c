#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  size; scalar_t__ offset; } ;
typedef  TYPE_1__ MyElf_Section ;
typedef  TYPE_2__ MyElf_File ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

unsigned char* GetElfSectionData(MyElf_File *elf, MyElf_Section *section) {

    unsigned char *data = 0;
    
	if (section->size && section->offset) {

		data = (unsigned char*)malloc(section->size);
		if(!data) {
	        error("Error: Out of memory!\r\n");
			return 0;
		}
            
		if(fseek(elf->fd, section->offset, SEEK_SET) ||
		   fread(data, 1, section->size, elf->fd) != section->size) {
			error("Error: Can't read section '%s' data from elf file.\r\n", section->name);
			free(data);
			return 0;
	    }

	} else {
		error("Error: Section '%s' has no data to read.\r\n", section->name);
	}

    return data;
}