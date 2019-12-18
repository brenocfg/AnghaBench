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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct sch2_header {scalar_t__ header_crc32; int header_length; int image_len; scalar_t__ image_crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_sch2_header (struct sch2_header*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int check_sch2_header(char *buf, struct sch2_header *header)
{

	int ret = EXIT_FAILURE;

	uint32_t crc32_tmp = header->header_crc32;
	header->header_crc32 = 0;

	if (crc32_tmp == crc32(0, (uint8_t *) header, header->header_length)) {
		uint32_t crc32_val;
		printf("Find proper SCH2 header at: 0x%lX!\n",
		       (char *)header - buf);

		crc32_val =
		    crc32(0, (uint8_t *) header + header->header_length,
			  header->image_len);
		if (header->image_crc32 == crc32_val) {
			printf("Kernel checksum ok.\n");

			header->header_crc32 = crc32_tmp;
			print_sch2_header(header);
			ret = EXIT_SUCCESS;
		} else
			ERR("Kernel checksum incorrect! Stored: 0x%X Calculated: 0x%X\n", header->image_crc32, crc32_val);

	} else
		ERR("SCH2 header checksum incorrect!");

	header->header_crc32 = crc32_tmp;
	return ret;
}