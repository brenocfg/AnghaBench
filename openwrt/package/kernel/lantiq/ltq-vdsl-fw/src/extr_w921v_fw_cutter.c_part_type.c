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

/* Variables and functions */
#define  MAGIC_ANNEX_B 129 
#define  MAGIC_TAPI 128 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

const char* part_type(unsigned int id)
{
	switch(id) {
	case MAGIC_ANNEX_B:
		return "/tmp/vr9_dsl_fw_annex_b.bin";
	case MAGIC_TAPI:
		return "/tmp/vr9_tapi_fw.bin";
	}
	printf("\tUnknown lzma type 0x%02X\n", id);
	return "/tmp/unknown.lzma";
}