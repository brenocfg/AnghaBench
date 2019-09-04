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
struct cdb_make {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ cdb_make_write (struct cdb_make*,char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  uint32_pack (char*,unsigned int) ; 

int cdb_make_addbegin(struct cdb_make *c, unsigned int keylen, unsigned int datalen)
{
	char buf[8];

	if (keylen > 0xffffffff) {
		errno = ENOMEM;
		return -1;
	}
	if (datalen > 0xffffffff) {
		errno = ENOMEM;
		return -1;
	}

	uint32_pack(buf, keylen);
	uint32_pack(buf + 4, datalen);
	if (cdb_make_write(c, buf, 8) != 0)
		return -1;
	return 0;
}