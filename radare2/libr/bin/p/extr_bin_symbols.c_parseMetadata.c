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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  nm3 ;
typedef  int /*<<< orphan*/  nm2 ;
typedef  int /*<<< orphan*/  nm ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_3__ {int addr; int cputype; int subtype; int n_segments; int namelen; int size; int /*<<< orphan*/  segments; int /*<<< orphan*/  cpu; int /*<<< orphan*/  bits; int /*<<< orphan*/  arch; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SymbolsMetadata ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  parseSegments (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int r_read_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subtypeString (int) ; 
 int /*<<< orphan*/  typeString (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SymbolsMetadata parseMetadata(RBuffer *buf, int off) {
	SymbolsMetadata sm = { 0 };
	ut8 b[0x100] = { 0 };
	(void)r_buf_read_at (buf, off, b, sizeof (b));
	sm.addr = off;
	sm.cputype = r_read_le32 (b);
	sm.arch = typeString (sm.cputype, &sm.bits);
	//  eprintf ("0x%08x  cputype  0x%x -> %s\n", 0x40, sm.cputype, typeString (sm.cputype));
	// bits = (strstr (typeString (sm.cputype, &sm.bits), "64"))? 64: 32;
	sm.subtype = r_read_le32 (b + 4);
	sm.cpu = subtypeString (sm.subtype);
	//  eprintf ("0x%08x  subtype  0x%x -> %s\n", 0x44, sm.subtype, subtypeString (sm.subtype));
	sm.n_segments = r_read_le32 (b + 8);
	// int count = r_read_le32 (b + 0x48);
	sm.namelen = r_read_le32 (b + 0xc);
	// eprintf ("0x%08x  count    %d\n", 0x48, count);
	// eprintf ("0x%08x  strlen   %d\n", 0x4c, sm.namelen);
	// eprintf ("0x%08x  filename %s\n", 0x50, b + 16);
	int delta = 16;
	sm.segments = parseSegments (buf, off + sm.namelen + delta, sm.n_segments);
	sm.size = (sm.n_segments * 32) + 120;

	// hack to detect format
	ut32 nm, nm2, nm3;
	r_buf_read_at (buf, off + sm.size, (ut8*)&nm, sizeof (nm));
	r_buf_read_at (buf, off + sm.size + 4, (ut8*)&nm2, sizeof (nm2));
	r_buf_read_at (buf, off + sm.size + 8, (ut8*)&nm3, sizeof (nm3));
	// eprintf ("0x%x next %x %x %x\n", off + sm.size, nm, nm2, nm3);
	if (r_read_le32 (&nm3) != 0xa1b22b1a) {
		sm.size -= 8;
		//		is64 = true;
	}
	return sm;
}