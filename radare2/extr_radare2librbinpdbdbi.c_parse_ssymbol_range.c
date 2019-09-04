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
struct TYPE_3__ {int /*<<< orphan*/  reloc_crc; int /*<<< orphan*/  data_crc; int /*<<< orphan*/  module; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  padding1; int /*<<< orphan*/  section; } ;
typedef  TYPE_1__ SSymbolRange ;

/* Variables and functions */
 int /*<<< orphan*/  READ2 (int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st16 ; 
 int /*<<< orphan*/  st32 ; 
 int /*<<< orphan*/  ut32 ; 

__attribute__((used)) static int parse_ssymbol_range(char *data, int max_len, SSymbolRange *symbol_range) {
	int read_bytes = 0;

	READ2(read_bytes, max_len, symbol_range->section, data, st16);
	READ2(read_bytes, max_len, symbol_range->padding1, data, st16);
	READ4(read_bytes, max_len, symbol_range->offset, data, st32);
	READ4(read_bytes, max_len, symbol_range->size, data, st32);
	READ4(read_bytes, max_len, symbol_range->flags, data, ut32);
	READ4(read_bytes, max_len, symbol_range->module, data, st32);

// TODO: why not need to read this padding?
//	READ2(read_bytes, max_len, symbol_range->padding2, data, short);
	READ4(read_bytes, max_len, symbol_range->data_crc, data, ut32);
	READ4(read_bytes, max_len, symbol_range->reloc_crc, data, ut32);

	return read_bytes;
}