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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tag {int /*<<< orphan*/  tagLocation; void* tagSerialNum; void* descVersion; void* tagIdent; } ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_update_tag (char*,int) ; 

void udf_new_tag(char *data, uint16_t ident, uint16_t version, uint16_t snum,
		 uint32_t loc, int length)
{
	struct tag *tptr = (struct tag *)data;
	tptr->tagIdent = cpu_to_le16(ident);
	tptr->descVersion = cpu_to_le16(version);
	tptr->tagSerialNum = cpu_to_le16(snum);
	tptr->tagLocation = cpu_to_le32(loc);
	udf_update_tag(data, length);
}