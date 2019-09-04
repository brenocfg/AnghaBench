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
struct TYPE_3__ {int /*<<< orphan*/  image_base; int /*<<< orphan*/  heap_nbytes; int /*<<< orphan*/  stack_nbytes; int /*<<< orphan*/  code_offset; int /*<<< orphan*/  argv_index; int /*<<< orphan*/  heap_index; int /*<<< orphan*/  stack_index; int /*<<< orphan*/  code_index; int /*<<< orphan*/  fpu; int /*<<< orphan*/  cpu; int /*<<< orphan*/  cflags; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ lmf_header ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ QNX_HDR_SIZE ; 
 int /*<<< orphan*/  QNX_HEADER_ADDR ; 
 scalar_t__ r_buf_fread_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lmf_header_load(lmf_header *lmfh, RBuffer *buf, Sdb *db) {
	if (r_buf_size (buf) < sizeof (lmf_header)) {
		return false;
	}
	if (r_buf_fread_at (buf, QNX_HEADER_ADDR, (ut8 *) lmfh, "iiiiiiiicccciiiicc", 1) < QNX_HDR_SIZE) {
		return false;
	}
	sdb_set (db, "qnx.version", sdb_fmt ("0x%xH", lmfh->version), 0);
	sdb_set (db, "qnx.cflags", sdb_fmt ("0x%xH", lmfh->cflags), 0);
	sdb_set (db, "qnx.cpu", sdb_fmt ("0x%xH", lmfh->cpu), 0);
	sdb_set (db, "qnx.fpu", sdb_fmt ("0x%xH", lmfh->fpu), 0);
	sdb_set (db, "qnx.code_index", sdb_fmt ("0x%x", lmfh->code_index), 0);
	sdb_set (db, "qnx.stack_index", sdb_fmt ("0x%x", lmfh->stack_index), 0);
	sdb_set (db, "qnx.heap_index", sdb_fmt ("0x%x", lmfh->heap_index), 0);
	sdb_set (db, "qnx.argv_index", sdb_fmt ("0x%x", lmfh->argv_index), 0);
	sdb_set (db, "qnx.code_offset", sdb_fmt ("0x%x", lmfh->code_offset), 0);
	sdb_set (db, "qnx.stack_nbytes", sdb_fmt ("0x%x", lmfh->stack_nbytes), 0);
	sdb_set (db, "qnx.heap_nbytes", sdb_fmt ("0x%x", lmfh->heap_nbytes), 0);
	sdb_set (db, "qnx.image_base", sdb_fmt ("0x%x", lmfh->image_base), 0);
	return true;
}