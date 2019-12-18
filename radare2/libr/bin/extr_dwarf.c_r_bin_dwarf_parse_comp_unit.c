#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_21__ {int length; } ;
struct TYPE_16__ {char* string; } ;
struct TYPE_17__ {TYPE_2__ str_struct; } ;
struct TYPE_20__ {scalar_t__ name; TYPE_3__ encoding; } ;
struct TYPE_19__ {size_t length; size_t capacity; TYPE_10__* dies; TYPE_9__ hdr; } ;
struct TYPE_18__ {int length; int capacity; TYPE_1__* decls; } ;
struct TYPE_15__ {size_t length; size_t capacity; int /*<<< orphan*/ * specs; int /*<<< orphan*/  tag; } ;
struct TYPE_14__ {int abbrev_code; size_t length; size_t capacity; TYPE_8__* attr_values; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_4__ RBinDwarfDebugAbbrev ;
typedef  TYPE_5__ RBinDwarfCompUnit ;

/* Variables and functions */
 scalar_t__ DW_AT_comp_dir ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_bin_dwarf_expand_cu (TYPE_5__*) ; 
 int /*<<< orphan*/  r_bin_dwarf_expand_die (TYPE_10__*) ; 
 int /*<<< orphan*/  r_bin_dwarf_init_die (TYPE_10__*) ; 
 int /*<<< orphan*/ * r_bin_dwarf_parse_attr_value (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,TYPE_8__*,TYPE_9__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * r_uleb128 (int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const ut8 *r_bin_dwarf_parse_comp_unit(Sdb *s, const ut8 *obuf,
		RBinDwarfCompUnit *cu, const RBinDwarfDebugAbbrev *da,
		size_t offset, const ut8 *debug_str, size_t debug_str_len) {
	const ut8 *buf = obuf, *buf_end = obuf + (cu->hdr.length - 7);
	ut64 abbr_code;
	size_t i;
	
	if (cu->hdr.length > debug_str_len) {
		//avoid oob read
		return NULL;
	}
	while (buf && buf < buf_end && buf >= obuf) {
		if (cu->length && cu->capacity == cu->length) {
			r_bin_dwarf_expand_cu (cu);
		}
		buf = r_uleb128 (buf, buf_end - buf, &abbr_code);
		if (abbr_code > da->length || !buf) {
			return NULL;
		}

		r_bin_dwarf_init_die (&cu->dies[cu->length]);
		if (!abbr_code) {
			cu->dies[cu->length].abbrev_code = 0;
			cu->length++;
			buf++;
			continue;
		}

		cu->dies[cu->length].abbrev_code = abbr_code;
		cu->dies[cu->length].tag = da->decls[abbr_code - 1].tag;
		abbr_code += offset;

		if (da->capacity < abbr_code) {
			return NULL;
		}

		for (i = 0; i < da->decls[abbr_code - 1].length; i++) {
			if (cu->dies[cu->length].length == cu->dies[cu->length].capacity) {
				r_bin_dwarf_expand_die (&cu->dies[cu->length]);
			}
			if (i >= cu->dies[cu->length].capacity || i >= da->decls[abbr_code - 1].capacity) {
				eprintf ("Warning: malformed dwarf attribute capacity doesn't match length\n");
				break;
			}
			memset (&cu->dies[cu->length].attr_values[i], 0, sizeof (cu->dies[cu->length].attr_values[i]));
			buf = r_bin_dwarf_parse_attr_value (buf, buf_end - buf,
					&da->decls[abbr_code - 1].specs[i],
					&cu->dies[cu->length].attr_values[i],
					&cu->hdr, debug_str, debug_str_len);
			if (cu->dies[cu->length].attr_values[i].name == DW_AT_comp_dir) {
				const char *name = cu->dies[cu->length].attr_values[i].encoding.str_struct.string;
				if ((size_t)name > 1024) { // solve some null derefs
					sdb_set (s, "DW_AT_comp_dir", name, 0);
				} else {
					eprintf ("Invalid string pointer at %p\n", name);
				}
			}
			cu->dies[cu->length].length++;
		}
		cu->length++;
	}
	return buf;
}