#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct dso {char* long_name; int /*<<< orphan*/ * dwfl; } ;
typedef  int /*<<< orphan*/  Dwfl_Module ;
typedef  int /*<<< orphan*/  Dwfl ;
typedef  int /*<<< orphan*/  Dwarf_Frame ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int check_return_reg (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_errmsg (int) ; 
 int dwarf_frame_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * dwfl_addrmodule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dwfl_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwfl_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwfl_report_elf (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_dwarf_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_eh_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offline_callbacks ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_return_addr(struct dso *dso, u64 map_start, Dwarf_Addr pc)
{
	int		rc = -1;
	Dwfl		*dwfl;
	Dwfl_Module	*mod;
	Dwarf_Frame	*frame;
	int		ra_regno;
	Dwarf_Addr	start = pc;
	Dwarf_Addr	end = pc;
	bool		signalp;
	const char	*exec_file = dso->long_name;

	dwfl = dso->dwfl;

	if (!dwfl) {
		dwfl = dwfl_begin(&offline_callbacks);
		if (!dwfl) {
			pr_debug("dwfl_begin() failed: %s\n", dwarf_errmsg(-1));
			return -1;
		}

		mod = dwfl_report_elf(dwfl, exec_file, exec_file, -1,
						map_start, false);
		if (!mod) {
			pr_debug("dwfl_report_elf() failed %s\n",
						dwarf_errmsg(-1));
			/*
			 * We normally cache the DWARF debug info and never
			 * call dwfl_end(). But to prevent fd leak, free in
			 * case of error.
			 */
			dwfl_end(dwfl);
			goto out;
		}
		dso->dwfl = dwfl;
	}

	mod = dwfl_addrmodule(dwfl, pc);
	if (!mod) {
		pr_debug("dwfl_addrmodule() failed, %s\n", dwarf_errmsg(-1));
		goto out;
	}

	/*
	 * To work with split debug info files (eg: glibc), check both
	 * .eh_frame and .debug_frame sections of the ELF header.
	 */
	frame = get_eh_frame(mod, pc);
	if (!frame) {
		frame = get_dwarf_frame(mod, pc);
		if (!frame)
			goto out;
	}

	ra_regno = dwarf_frame_info(frame, &start, &end, &signalp);
	if (ra_regno < 0) {
		pr_debug("Return address register unavailable: %s\n",
				dwarf_errmsg(-1));
		goto out;
	}

	rc = check_return_reg(ra_regno, frame);

out:
	return rc;
}