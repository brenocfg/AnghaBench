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
struct btf {int dummy; } ;
struct bpf_line_info {int /*<<< orphan*/  line_col; int /*<<< orphan*/  file_name_off; int /*<<< orphan*/  line_off; } ;

/* Variables and functions */
 scalar_t__ BPF_LINE_INFO_LINE_COL (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_LINE_INFO_LINE_NUM (int /*<<< orphan*/ ) ; 
 char* btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_int_field (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  jsonw_string_field (int /*<<< orphan*/ ,char*,char const*) ; 
 char const* ltrim (char const*) ; 

void btf_dump_linfo_json(const struct btf *btf,
			 const struct bpf_line_info *linfo, bool linum)
{
	const char *line = btf__name_by_offset(btf, linfo->line_off);

	if (line)
		jsonw_string_field(json_wtr, "src", ltrim(line));

	if (linum) {
		const char *file = btf__name_by_offset(btf, linfo->file_name_off);

		if (file)
			jsonw_string_field(json_wtr, "file", file);

		if (BPF_LINE_INFO_LINE_NUM(linfo->line_col))
			jsonw_int_field(json_wtr, "line_num",
					BPF_LINE_INFO_LINE_NUM(linfo->line_col));

		if (BPF_LINE_INFO_LINE_COL(linfo->line_col))
			jsonw_int_field(json_wtr, "line_col",
					BPF_LINE_INFO_LINE_COL(linfo->line_col));
	}
}