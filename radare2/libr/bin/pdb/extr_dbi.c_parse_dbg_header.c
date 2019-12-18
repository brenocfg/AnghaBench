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
struct TYPE_3__ {int /*<<< orphan*/  sn_section_hdr_orig; int /*<<< orphan*/  sn_new_fpo; int /*<<< orphan*/  sn_pdata; int /*<<< orphan*/  sn_xdata; int /*<<< orphan*/  sn_token_rid_map; int /*<<< orphan*/  sn_section_hdr; int /*<<< orphan*/  sn_omap_from_src; int /*<<< orphan*/  sn_omap_to_src; int /*<<< orphan*/  sn_fixup; int /*<<< orphan*/  sn_exception; int /*<<< orphan*/  sn_fpo; } ;
typedef  TYPE_1__ SDbiDbgHeader ;
typedef  int /*<<< orphan*/  R_STREAM_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  stream_file_read (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void parse_dbg_header(SDbiDbgHeader *dbg_header, R_STREAM_FILE *stream_file) {
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_fpo);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_exception);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_fixup);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_omap_to_src);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_omap_from_src);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_section_hdr);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_token_rid_map);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_xdata);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_pdata);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_new_fpo);
	stream_file_read (stream_file, sizeof (short), (char *)&dbg_header->sn_section_hdr_orig);
}