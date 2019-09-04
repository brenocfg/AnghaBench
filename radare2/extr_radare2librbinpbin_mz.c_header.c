#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct r_bin_mz_obj_t {TYPE_2__* dos_header; } ;
struct TYPE_7__ {TYPE_1__* o; } ;
struct TYPE_6__ {int signature; int /*<<< orphan*/  overlay_number; int /*<<< orphan*/  reloc_table_offset; int /*<<< orphan*/  cs; int /*<<< orphan*/  ip; int /*<<< orphan*/  checksum; int /*<<< orphan*/  sp; int /*<<< orphan*/  ss; int /*<<< orphan*/  max_extra_paragraphs; int /*<<< orphan*/  min_extra_paragraphs; int /*<<< orphan*/  header_paragraphs; int /*<<< orphan*/  num_relocs; int /*<<< orphan*/  blocks_in_file; int /*<<< orphan*/  bytes_in_last_block; } ;
struct TYPE_5__ {scalar_t__ bin_obj; } ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,int,...) ; 

__attribute__((used)) static void header(RBinFile *bf) {
	const struct r_bin_mz_obj_t *mz = (struct r_bin_mz_obj_t *)bf->o->bin_obj;
	eprintf ("[0000:0000]  Signature           %c%c\n",
		mz->dos_header->signature & 0xFF,
		mz->dos_header->signature >> 8);
	eprintf ("[0000:0002]  BytesInLastBlock    0x%04x\n",
		mz->dos_header->bytes_in_last_block);
	eprintf ("[0000:0004]  BlocksInFile        0x%04x\n",
		mz->dos_header->blocks_in_file);
	eprintf ("[0000:0006]  NumRelocs           0x%04x\n",
		mz->dos_header->num_relocs);
	eprintf ("[0000:0008]  HeaderParagraphs    0x%04x\n",
		mz->dos_header->header_paragraphs);
	eprintf ("[0000:000a]  MinExtraParagraphs  0x%04x\n",
		mz->dos_header->min_extra_paragraphs);
	eprintf ("[0000:000c]  MaxExtraParagraphs  0x%04x\n",
		mz->dos_header->max_extra_paragraphs);
	eprintf ("[0000:000e]  InitialSs           0x%04x\n",
		mz->dos_header->ss);
	eprintf ("[0000:0010]  InitialSp           0x%04x\n",
		mz->dos_header->sp);
	eprintf ("[0000:0012]  Checksum            0x%04x\n",
		mz->dos_header->checksum);
	eprintf ("[0000:0014]  InitialIp           0x%04x\n",
		mz->dos_header->ip);
	eprintf ("[0000:0016]  InitialCs           0x%04x\n",
		mz->dos_header->cs);
	eprintf ("[0000:0018]  RelocTableOffset    0x%04x\n",
		mz->dos_header->reloc_table_offset);
	eprintf ("[0000:001a]  OverlayNumber       0x%04x\n",
		mz->dos_header->overlay_number);
}