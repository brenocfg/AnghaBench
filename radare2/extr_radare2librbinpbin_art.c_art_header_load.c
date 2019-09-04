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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {int /*<<< orphan*/  compile_pic; int /*<<< orphan*/  image_roots; int /*<<< orphan*/  patch_delta; int /*<<< orphan*/  oat_data_end; int /*<<< orphan*/  oat_data_begin; int /*<<< orphan*/  oat_file_end; int /*<<< orphan*/  oat_file_begin; int /*<<< orphan*/ * version; int /*<<< orphan*/  checksum; int /*<<< orphan*/  image_size; int /*<<< orphan*/  image_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; TYPE_2__ art; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ ArtObj ;
typedef  TYPE_2__ ARTHeader ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_fread_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_fmt (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int art_header_load(ArtObj *ao, Sdb *db) {
	/* TODO: handle read errors here */
	if (r_buf_size (ao->buf) < sizeof (ARTHeader)) {
		return false;
	}
	ARTHeader *art = &ao->art;
	(void) r_buf_fread_at (ao->buf, 0, (ut8 *) art, "IIiiiiiiiiiiii", 1);
	sdb_set (db, "img.base", sdb_fmt ("0x%x", art->image_base), 0);
	sdb_set (db, "img.size", sdb_fmt ("0x%x", art->image_size), 0);
	sdb_set (db, "art.checksum", sdb_fmt ("0x%x", art->checksum), 0);
	sdb_set (db, "art.version", sdb_fmt ("%c%c%c",
			art->version[0], art->version[1], art->version[2]), 0);
	sdb_set (db, "oat.begin", sdb_fmt ("0x%x", art->oat_file_begin), 0);
	sdb_set (db, "oat.end", sdb_fmt ("0x%x", art->oat_file_end), 0);
	sdb_set (db, "oat_data.begin", sdb_fmt ("0x%x", art->oat_data_begin), 0);
	sdb_set (db, "oat_data.end", sdb_fmt ("0x%x", art->oat_data_end), 0);
	sdb_set (db, "patch_delta", sdb_fmt ("0x%x", art->patch_delta), 0);
	sdb_set (db, "image_roots", sdb_fmt ("0x%x", art->image_roots), 0);
	sdb_set (db, "compile_pic", sdb_fmt ("0x%x", art->compile_pic), 0);
	return true;
}