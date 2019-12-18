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
struct TYPE_5__ {TYPE_1__* panels; } ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 char* PANEL_TITLE_STRINGS_BIN ; 
 char* PANEL_TITLE_STRINGS_DATA ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

void __init_sdb(RCore *core) {
	RPanels *panels = core->panels;
	sdb_set (panels->db, "Symbols", "isq", 0);
	sdb_set (panels->db, "Stack"  , "px 256@r:SP", 0);
	sdb_set (panels->db, "Locals", "afvd", 0);
	sdb_set (panels->db, "Registers", "dr", 0);
	sdb_set (panels->db, "RegisterRefs", "drr", 0);
	sdb_set (panels->db, "Disassembly", "pd", 0);
	sdb_set (panels->db, "Disassemble Summary", "pdsf", 0);
	sdb_set (panels->db, "Decompiler", "pdc", 0);
	sdb_set (panels->db, "Decompiler With Offsets", "pddo", 0);
	sdb_set (panels->db, "Graph", "agf", 0);
	sdb_set (panels->db, "Tiny Graph", "agft", 0);
	sdb_set (panels->db, "Info", "i", 0);
	sdb_set (panels->db, "Database", "k ***", 0);
	sdb_set (panels->db, "Console", "$console", 0);
	sdb_set (panels->db, "Hexdump", "xc $r*16", 0);
	sdb_set (panels->db, "Xrefs", "ax", 0);
	sdb_set (panels->db, "Xrefs Here", "ax.", 0);
	sdb_set (panels->db, "Functions", "afl", 0);
	sdb_set (panels->db, "Function Calls", "aflm", 0);
	sdb_set (panels->db, "Comments", "CC", 0);
	sdb_set (panels->db, "Entropy", "p=e 100", 0);
	sdb_set (panels->db, "Entropy Fire", "p==e 100", 0);
	sdb_set (panels->db, "DRX", "drx", 0);
	sdb_set (panels->db, "Sections", "iSq", 0);
	sdb_set (panels->db, "Segments", "iSSq", 0);
	sdb_set (panels->db, PANEL_TITLE_STRINGS_DATA, "izq", 0);
	sdb_set (panels->db, PANEL_TITLE_STRINGS_BIN, "izzq", 0);
	sdb_set (panels->db, "Maps", "dm", 0);
	sdb_set (panels->db, "Modules", "dmm", 0);
	sdb_set (panels->db, "Backtrace", "dbt", 0);
	sdb_set (panels->db, "Breakpoints", "db", 0);
	sdb_set (panels->db, "Imports", "iiq", 0);
	sdb_set (panels->db, "Clipboard", "yx", 0);
	sdb_set (panels->db, "New", "o", 0);
	sdb_set (panels->db, "Var READ address", "afvR", 0);
	sdb_set (panels->db, "Var WRITE address", "afvW", 0);
	sdb_set (panels->db, "Summary", "pdsf", 0);
	sdb_set (panels->db, "Classes", "icq", 0);
	sdb_set (panels->db, "Methods", "ic", 0);
	sdb_set (panels->db, "Relocs", "ir", 0);
	sdb_set (panels->db, "Headers", "iH", 0);
	sdb_set (panels->db, "File Hashes", "it", 0);
}