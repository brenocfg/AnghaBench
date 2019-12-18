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
typedef  size_t ut32 ;
struct TYPE_5__ {size_t num_bits; size_t num_fields; TYPE_1__* fields; } ;
typedef  TYPE_2__ gdbr_xml_flags_t ;
struct TYPE_4__ {int sz; size_t bit_num; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 size_t tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _write_flag_bits(char *buf, const gdbr_xml_flags_t *flags) {
	bool fc[26] = { false };
	ut32 i, c;
	memset (buf, '.', flags->num_bits);
	buf[flags->num_bits] = '\0';
	for (i = 0; i < flags->num_fields; i++) {
		// How do we show multi-bit flags?
		if (flags->fields[i].sz != 1) {
			continue;
		}
		// To avoid duplicates. This skips flags if first char is same. i.e.
		// for x86_64, it will skip VIF because VM already occured. This is
		// same as default reg-profiles in r2
		c = tolower (flags->fields[i].name[0]) - 'a';
		if (fc[c]) {
			continue;
		}
		fc[c] = true;
		buf[flags->fields[i].bit_num] = 'a' + c;
	}
}