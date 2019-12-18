#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  leaf_type; scalar_t__ type_info; } ;
struct TYPE_8__ {int ti_min; int ti_max; } ;
struct TYPE_10__ {int /*<<< orphan*/  types; TYPE_1__ header; } ;
struct TYPE_9__ {int tpi_idx; TYPE_6__ type_data; } ;
typedef  TYPE_2__ SType ;
typedef  TYPE_3__ STpiStream ;
typedef  int /*<<< orphan*/  STPIHeader ;
typedef  int /*<<< orphan*/  R_STREAM_FILE ;

/* Variables and functions */
 int base_idx ; 
 int /*<<< orphan*/  eLF_MAX ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  init_stype_info (TYPE_6__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  p_types_list ; 
 int /*<<< orphan*/  parse_tpi_stypes (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_new () ; 
 int /*<<< orphan*/  stream_file_read (int /*<<< orphan*/ *,int,char*) ; 

int parse_tpi_stream(void *parsed_pdb_stream, R_STREAM_FILE *stream) {
	int i;
	SType *type = 0;
	STpiStream *tpi_stream = (STpiStream *) parsed_pdb_stream;
	tpi_stream->types = r_list_new ();
	p_types_list = tpi_stream->types;

	stream_file_read(stream, sizeof(STPIHeader), (char *)&tpi_stream->header);

	base_idx = tpi_stream->header.ti_min;

	for (i = tpi_stream->header.ti_min; i < tpi_stream->header.ti_max; i++) {
		type = (SType *) malloc (sizeof (SType));
		if (!type) {
			return 0;
		}
		type->tpi_idx = i;
		type->type_data.type_info = 0;
		type->type_data.leaf_type = eLF_MAX;
		init_stype_info(&type->type_data);
		if (!parse_tpi_stypes(stream, type)) {
			free (type);
			return 0;
		}
		r_list_append(tpi_stream->types, type);
	}
	return 1;
}