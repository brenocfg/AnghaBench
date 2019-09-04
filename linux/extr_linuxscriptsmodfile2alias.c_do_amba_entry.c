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
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amba_id ; 
 int /*<<< orphan*/  append_nibble_mask (char**,int,int) ; 
 int /*<<< orphan*/  fatal (char*,char const*,int,int) ; 
 int id ; 
 int mask ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static int do_amba_entry(const char *filename,
			 void *symval, char *alias)
{
	unsigned int digit;
	char *p = alias;
	DEF_FIELD(symval, amba_id, id);
	DEF_FIELD(symval, amba_id, mask);

	if ((id & mask) != id)
		fatal("%s: Masked-off bit(s) of AMBA device ID are non-zero: "
		      "id=0x%08X, mask=0x%08X.  Please fix this driver.\n",
		      filename, id, mask);

	p += sprintf(alias, "amba:d");
	for (digit = 0; digit < 8; digit++)
		append_nibble_mask(&p,
				   (id >> (4 * (7 - digit))) & 0xf,
				   (mask >> (4 * (7 - digit))) & 0xf);

	return 1;
}