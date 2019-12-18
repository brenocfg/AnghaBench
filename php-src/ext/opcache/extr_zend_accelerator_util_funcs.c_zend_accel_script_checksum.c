#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; int /*<<< orphan*/  dynamic_members; scalar_t__ mem; } ;
typedef  TYPE_1__ zend_persistent_script ;

/* Variables and functions */
 unsigned int ADLER32_INIT ; 
 unsigned int zend_adler32 (unsigned int,unsigned char*,size_t) ; 

unsigned int zend_accel_script_checksum(zend_persistent_script *persistent_script)
{
	unsigned char *mem = (unsigned char*)persistent_script->mem;
	size_t size = persistent_script->size;
	size_t persistent_script_check_block_size = ((char *)&(persistent_script->dynamic_members)) - (char *)persistent_script;
	unsigned int checksum = ADLER32_INIT;

	if (mem < (unsigned char*)persistent_script) {
		checksum = zend_adler32(checksum, mem, (unsigned char*)persistent_script - mem);
		size -= (unsigned char*)persistent_script - mem;
		mem  += (unsigned char*)persistent_script - mem;
	}

	zend_adler32(checksum, mem, persistent_script_check_block_size);
	mem  += sizeof(*persistent_script);
	size -= sizeof(*persistent_script);

	if (size > 0) {
		checksum = zend_adler32(checksum, mem, size);
	}
	return checksum;
}