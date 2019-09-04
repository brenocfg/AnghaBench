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
struct TYPE_3__ {int /*<<< orphan*/  sdb; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/  sdb_ns_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Sdb *get_sdb(RBinFile *bf) {
	Sdb *kv = sdb_new0 ();
	sdb_num_set (kv, "nro_start.offset", 0, 0);
	sdb_num_set (kv, "nro_start.size", 16, 0);
	sdb_set (kv, "nro_start.format", "xxq unused mod_memoffset padding", 0);
	sdb_num_set (kv, "nro_header.offset", 16, 0);
	sdb_num_set (kv, "nro_header.size", 0x70, 0);
	sdb_set (kv, "nro_header.format", "xxxxxxxxxxxx magic unk size unk2 text_offset text_size ro_offset ro_size data_offset data_size bss_size unk3", 0);
	sdb_ns_set (bf->sdb, "info", kv);
	return kv;
}