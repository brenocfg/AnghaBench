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
struct ubifs_info {int /*<<< orphan*/  max_write_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int chance (int,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,unsigned int) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prandom_bytes (unsigned char*,unsigned int) ; 
 unsigned int prandom_u32 () ; 
 int /*<<< orphan*/  ubifs_warn (struct ubifs_info const*,char*,unsigned int,unsigned int,char*) ; 

__attribute__((used)) static int corrupt_data(const struct ubifs_info *c, const void *buf,
			unsigned int len)
{
	unsigned int from, to, ffs = chance(1, 2);
	unsigned char *p = (void *)buf;

	from = prandom_u32() % len;
	/* Corruption span max to end of write unit */
	to = min(len, ALIGN(from + 1, c->max_write_size));

	ubifs_warn(c, "filled bytes %u-%u with %s", from, to - 1,
		   ffs ? "0xFFs" : "random data");

	if (ffs)
		memset(p + from, 0xFF, to - from);
	else
		prandom_bytes(p + from, to - from);

	return to;
}