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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_2__ {int version; int paddr; int vaddr; int psize; int cert_va; int cert_sz; int sign_va; int sign_sz; int load_index; } ;
typedef  int /*<<< orphan*/  SBLHDR ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_fread_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new_with_pointers (int /*<<< orphan*/  const*,int) ; 
 TYPE_1__ sb ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 bufsz) {
	if (buf && bufsz >= sizeof (SBLHDR)) {
		RBuffer *b = r_buf_new_with_pointers (buf, bufsz);
		int ret = r_buf_fread_at (b, 0, (ut8*)&sb, "10i", 1);
		r_buf_free (b);
		if (!ret) {
			return false;
		}
		if (sb.version != 3) { // NAND
			return false;
		}
		if (sb.paddr + sizeof (SBLHDR) > bufsz) { // NAND
			return false;
		}
		if (sb.vaddr < 0x100 || sb.psize > bufsz) { // NAND
			return false;
		}
		if (sb.cert_va < sb.vaddr) {
			return false;
		}
		if (sb.cert_sz >= 0xf0000) {
			return false;
		}
		if (sb.sign_va < sb.vaddr) {
			return false;
		}
		if (sb.sign_sz >= 0xf0000) {
			return false;
		}
		if (sb.load_index < 1 || sb.load_index > 0x40) {
			return false; // should be 0x19 ?
		}
#if 0
		eprintf ("V=%d\n", sb.version);
		eprintf ("PA=0x%08x sz=0x%x\n", sb.paddr, sb.psize);
		eprintf ("VA=0x%08x sz=0x%x\n", sb.vaddr, sb.psize);
		eprintf ("CODE=0x%08x\n", sb.code_pa + sb.vaddr+40);
		eprintf ("SIGN=0x%08x sz=0x%x\n", sb.sign_va, sb.sign_sz);
		if (sb.cert_sz > 0) {
			eprintf ("CERT=0x%08x sz=0x%x\n", sb.cert_va, sb.cert_sz);
		} else {
			eprintf ("No certificate found.\n");
		}
#endif
// TODO: Add more checks here
		return true;
	}
	return false;
}