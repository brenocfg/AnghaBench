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
struct nsp_img_hdr_sections {int total_size; int raw_size; int offset; int type; char* name; } ;
struct nsp_img_hdr_section_info {int dummy; } ;
struct nsp_img_hdr_chksum {int hdr_chksum; } ;
struct TYPE_4__ {int sections_offset; int num_sects; } ;
struct TYPE_3__ {int magic; int hdr_size; int image_size; int prod_id; int rel_id; int version; int info_offset; int sect_info_offset; int chksum_offset; } ;
struct nsp_img_hdr {TYPE_2__ sect_info; struct nsp_img_hdr_sections sections; TYPE_1__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void mknspimg_print_hdr(struct nsp_img_hdr *hdr)
{
	struct nsp_img_hdr_chksum	*chksum;
	struct nsp_img_hdr_section_info	*sect_info;
	struct nsp_img_hdr_sections	*section;
	int i;

	printf("****************** NSP Image Summary ******************\n");
	printf("Magic:             0x%x\n",		hdr->head.magic);
	printf("Image Header Size: 0x%x bytes\n",	hdr->head.hdr_size);
	printf("Total Image Size:  %d bytes\n",		hdr->head.image_size);
	printf("Product ID:        0x%x\n",		hdr->head.prod_id);
	printf("Release ID:        0x%x\n",		hdr->head.rel_id);
	printf("Version ID:        0x%x\n",		hdr->head.version);

	printf("Offset Info:       0x%x\n",		hdr->head.info_offset);
	printf("Offset Sect info:  0x%x\n",		hdr->head.sect_info_offset);
	printf("Offset Sections:   0x%x\n",		hdr->sect_info.sections_offset);

	chksum=(struct nsp_img_hdr_chksum *)(hdr+hdr->head.chksum_offset);
	printf("Header Checksum:   0x%x\n",		chksum->hdr_chksum);

	printf("+++ Section Information +++\n");
	printf("# of sections:     %u\n", hdr->sect_info.num_sects);
	section=&(hdr->sections);
	for(i = 0; i < hdr->sect_info.num_sects; i++, section++) {
		printf("+++++ Section %d +++++\n", i);
		printf("Total size:  %u bytes\n",	section->total_size);
		printf("Raw Size:    %u bytes\n",	section->raw_size);
		printf("Offset:      0x%x\n",		section->offset);
		printf("Type:        0x%x\n",		section->type);
		printf("Name:        %s\n",		section->name);
	}
	printf("*******************************************************\n");
}