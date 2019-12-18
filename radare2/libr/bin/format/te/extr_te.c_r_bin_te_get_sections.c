#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r_bin_te_section_t {int last; int /*<<< orphan*/  flags; void* paddr; int /*<<< orphan*/  vsize; int /*<<< orphan*/  size; void* vaddr; int /*<<< orphan*/  name; } ;
struct r_bin_te_obj_t {TYPE_1__* header; TYPE_2__* section_header; } ;
struct TYPE_4__ {void* VirtualAddress; void* PointerToRawData; int /*<<< orphan*/  Characteristics; int /*<<< orphan*/  VirtualSize; int /*<<< orphan*/  SizeOfRawData; int /*<<< orphan*/  Name; } ;
struct TYPE_3__ {int NumberOfSections; } ;
typedef  TYPE_2__ TE_image_section_header ;

/* Variables and functions */
 int /*<<< orphan*/  TE_IMAGE_SIZEOF_NAME ; 
 struct r_bin_te_section_t* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 void* r_bin_te_get_stripped_delta (struct r_bin_te_obj_t*) ; 

struct r_bin_te_section_t* r_bin_te_get_sections(struct r_bin_te_obj_t* bin) {
	struct r_bin_te_section_t *sections = NULL;
	TE_image_section_header *shdr;
	int i, sections_count;
	if (!bin) {
		return NULL;
	}
	shdr = bin->section_header;
	sections_count = bin->header->NumberOfSections;

	if (!(sections = calloc ((sections_count + 1), sizeof (struct r_bin_te_section_t)))) {
		perror ("malloc (sections)");
		return NULL;
	}
	for (i = 0; i < sections_count; i++) {
		memcpy (sections[i].name, shdr[i].Name, TE_IMAGE_SIZEOF_NAME);
		// not a null terminated string if len==buflen
		//sections[i].name[TE_IMAGE_SIZEOF_NAME] = '\0';
		sections[i].vaddr = shdr[i].VirtualAddress - r_bin_te_get_stripped_delta (bin);
		sections[i].size = shdr[i].SizeOfRawData;
		sections[i].vsize = shdr[i].VirtualSize;
		sections[i].paddr = shdr[i].PointerToRawData - r_bin_te_get_stripped_delta (bin);
		sections[i].flags = shdr[i].Characteristics;
		sections[i].last = 0;
	}
	sections[i].last = 1;
	return sections;
}