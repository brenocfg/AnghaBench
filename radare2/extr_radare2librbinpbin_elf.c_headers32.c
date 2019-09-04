#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; TYPE_1__* rbin; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cb_printf ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_read_le16_at (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_buf_read_le32_at (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void headers32(RBinFile *bf) {
#define p bf->rbin->cb_printf
	p ("0x00000000  ELF MAGIC   0x%08x\n", r_buf_read_le32_at (bf->buf, 0));
	p ("0x00000010  Type        0x%04x\n", r_buf_read_le16_at (bf->buf, 0x10));
	p ("0x00000012  Machine     0x%04x\n", r_buf_read_le16_at (bf->buf, 0x12));
	p ("0x00000014  Version     0x%08x\n", r_buf_read_le32_at (bf->buf, 0x14));
	p ("0x00000018  Entrypoint  0x%08x\n", r_buf_read_le32_at (bf->buf, 0x18));
	p ("0x0000001c  PhOff       0x%08x\n", r_buf_read_le32_at (bf->buf, 0x1c));
	p ("0x00000020  ShOff       0x%08x\n", r_buf_read_le32_at (bf->buf, 0x20));
}