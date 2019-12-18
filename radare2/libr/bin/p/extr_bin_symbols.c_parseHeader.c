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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_3__ {int magic; int valid; int size; void* slotsize; void* unk1; void* unk0; int /*<<< orphan*/ * uuid; void* version; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SymbolsHeader ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void* r_read_le16 (int /*<<< orphan*/ *) ; 
 void* r_read_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SymbolsHeader parseHeader(RBuffer *buf) {
	ut8 b[64];
	SymbolsHeader sh = { 0 };
	(void)r_buf_read_at (buf, 0, b, sizeof (b));
	sh.magic = r_read_le32 (b);
	sh.version = r_read_le32 (b + 4);
	sh.valid = sh.magic == 0xff01ff02;
	int i;
	for (i = 0; i < 16; i++) {
		sh.uuid[i] = b[24 + i];
	}
	sh.unk0 = r_read_le16 (b + 0x28);
	sh.unk1 = r_read_le16 (b + 0x2c); // is slotsize + 1 :?
	sh.slotsize = r_read_le16 (b + 0x2e);
	sh.size = 0x40;
	return sh;
}