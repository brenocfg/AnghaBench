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
struct auh_header {char* rom_id; int derange; int image_checksum; int space1; int space2; int space3; int lpvs; int mbz; int time_stamp; int erase_start; int erase_length; int data_offset; int data_length; int space4; int space5; int space6; int space7; int header_id; int header_version; int space8; int section_id; int image_info_type; int image_info_offset; int family_member; int header_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

void print_auh_header(struct auh_header *printed_header)
{
	printf("\trom_id: %s\n"
	       "\tderange: 0x%04X\n"
	       "\timage_checksum: 0x%04X\n"
	       "\tspace1: 0x%08X\n"
	       "\tspace2: 0x%08X\n"
	       "\tspace3: 0x%04X\n"
	       "\tlpvs: 0x%02X\n"
	       "\tmbz: 0x%02X\n"
	       "\ttime_stamp: 0x%08X\n"
	       "\terase_start: 0x%08X\n"
	       "\terase_length: 0x%08X\n"
	       "\tdata_offset: 0x%08X\n"
	       "\tdata_length: 0x%08X\n"
	       "\tspace4: 0x%08X\n"
	       "\tspace5: 0x%08X\n"
	       "\tspace6: 0x%08X\n"
	       "\tspace7: 0x%08X\n"
	       "\theader_id: 0x%04X\n"
	       "\theader_version: 0x%02X\n"
	       "\tspace8: 0x%04X\n"
	       "\tsection_id: 0x%02X\n"
	       "\timage_info_type: 0x%02X\n"
	       "\timage_info_offset 0x%08X\n"
	       "\tfamily_member: 0x%04X\n"
	       "\theader_checksum: 0x%04X\n",
	       printed_header->rom_id,
	       printed_header->derange,
	       printed_header->image_checksum,
	       printed_header->space1,
	       printed_header->space2,
	       printed_header->space3,
	       printed_header->lpvs,
	       printed_header->mbz,
	       printed_header->time_stamp,
	       printed_header->erase_start,
	       printed_header->erase_length,
	       printed_header->data_offset,
	       printed_header->data_length,
	       printed_header->space4,
	       printed_header->space5,
	       printed_header->space6,
	       printed_header->space7,
	       printed_header->header_id,
	       printed_header->header_version,
	       printed_header->space8,
	       printed_header->section_id,
	       printed_header->image_info_type,
	       printed_header->image_info_offset,
	       printed_header->family_member, printed_header->header_checksum);
}