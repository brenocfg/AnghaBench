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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {char* checksum; } ;
typedef  TYPE_1__ tar_header ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_DIR_SEPARATOR ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ phar_tar_checksum (char*,int) ; 
 scalar_t__ phar_tar_number (char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strrchr (char*,int /*<<< orphan*/ ) ; 
 char* strstr (char*,char*) ; 

int phar_is_tar(char *buf, char *fname) /* {{{ */
{
	tar_header *header = (tar_header *) buf;
	uint32_t checksum = phar_tar_number(header->checksum, sizeof(header->checksum));
	uint32_t ret;
	char save[sizeof(header->checksum)], *bname;

	/* assume that the first filename in a tar won't begin with <?php */
	if (!strncmp(buf, "<?php", sizeof("<?php")-1)) {
		return 0;
	}

	memcpy(save, header->checksum, sizeof(header->checksum));
	memset(header->checksum, ' ', sizeof(header->checksum));
	ret = (checksum == phar_tar_checksum(buf, 512));
	memcpy(header->checksum, save, sizeof(header->checksum));
	if ((bname = strrchr(fname, PHP_DIR_SEPARATOR))) {
		fname = bname;
	}
	if (!ret && (bname = strstr(fname, ".tar")) && (bname[4] == '\0' || bname[4] == '.')) {
		/* probably a corrupted tar - so we will pretend it is one */
		return 1;
	}
	return ret;
}