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
struct TYPE_6__ {int /*<<< orphan*/  sn_token_rid_map; int /*<<< orphan*/  sn_pdata; int /*<<< orphan*/  sn_xdata; int /*<<< orphan*/  sn_new_fpo; int /*<<< orphan*/  sn_fpo; int /*<<< orphan*/  sn_omap_from_src; int /*<<< orphan*/  sn_omap_to_src; int /*<<< orphan*/  sn_section_hdr_orig; int /*<<< orphan*/  sn_section_hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  symrecStream; } ;
struct TYPE_7__ {TYPE_2__ dbg_header; TYPE_1__ dbi_header; } ;
typedef  int /*<<< orphan*/  SPEStream ;
typedef  int /*<<< orphan*/  SOmapStream ;
typedef  int /*<<< orphan*/  SGDATAStream ;
typedef  int /*<<< orphan*/  SFPOStream ;
typedef  int /*<<< orphan*/  SFPONewStream ;
typedef  TYPE_3__ SDbiStream ;
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_INDX_TO_LIST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ePDB_STREAM_FPO ; 
 int /*<<< orphan*/  ePDB_STREAM_FPO_NEW ; 
 int /*<<< orphan*/  ePDB_STREAM_GSYM ; 
 int /*<<< orphan*/  ePDB_STREAM_OMAP_FROM_SRC ; 
 int /*<<< orphan*/  ePDB_STREAM_OMAP_TO_SRC ; 
 int /*<<< orphan*/  ePDB_STREAM_PDATA ; 
 int /*<<< orphan*/  ePDB_STREAM_SECT_HDR ; 
 int /*<<< orphan*/  ePDB_STREAM_SECT__HDR_ORIG ; 
 int /*<<< orphan*/  ePDB_STREAM_TOKEN_RID_MAP ; 
 int /*<<< orphan*/  ePDB_STREAM_XDATA ; 
 int /*<<< orphan*/  free_fpo_stream ; 
 int /*<<< orphan*/  free_gdata_stream ; 
 int /*<<< orphan*/  free_omap_stream ; 
 int /*<<< orphan*/  free_pe_stream ; 
 int /*<<< orphan*/  parse_fpo_new_stream ; 
 int /*<<< orphan*/  parse_fpo_stream ; 
 int /*<<< orphan*/  parse_gdata_stream ; 
 int /*<<< orphan*/  parse_omap_stream ; 
 int /*<<< orphan*/  parse_pe_stream ; 

__attribute__((used)) static void fill_list_for_stream_parsing(RList *l, SDbiStream *dbi_stream) {
	ADD_INDX_TO_LIST (l, dbi_stream->dbi_header.symrecStream, sizeof (SGDATAStream),
		ePDB_STREAM_GSYM, free_gdata_stream, parse_gdata_stream);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_section_hdr, sizeof (SPEStream),
		ePDB_STREAM_SECT_HDR, free_pe_stream, parse_pe_stream);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_section_hdr_orig, sizeof(SPEStream),
		ePDB_STREAM_SECT__HDR_ORIG, free_pe_stream, parse_pe_stream);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_omap_to_src, sizeof(SOmapStream),
		ePDB_STREAM_OMAP_TO_SRC, free_omap_stream, parse_omap_stream);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_omap_from_src, sizeof(SOmapStream),
		ePDB_STREAM_OMAP_FROM_SRC, free_omap_stream, parse_omap_stream);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_fpo, sizeof(SFPOStream),
		ePDB_STREAM_FPO, free_fpo_stream, parse_fpo_stream);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_new_fpo, sizeof(SFPONewStream),
		ePDB_STREAM_FPO_NEW, free_fpo_stream, parse_fpo_new_stream);

	// unparsed, but know their names
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_xdata, 0, ePDB_STREAM_XDATA, 0, 0);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_pdata, 0, ePDB_STREAM_PDATA, 0, 0);
	ADD_INDX_TO_LIST (l, dbi_stream->dbg_header.sn_token_rid_map, 0, ePDB_STREAM_TOKEN_RID_MAP, 0, 0);
}