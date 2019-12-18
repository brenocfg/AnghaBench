#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  buf; TYPE_1__* stream_map; scalar_t__ pdb_streams2; scalar_t__ pdb_streams; TYPE_1__* root_stream; } ;
struct TYPE_14__ {struct TYPE_14__* stream; int /*<<< orphan*/  (* free ) (TYPE_1__*) ;scalar_t__ streams_list; struct TYPE_14__* stream_pages; } ;
typedef  TYPE_1__ STpiStream ;
typedef  TYPE_1__ SStreamParseFunc ;
typedef  TYPE_1__ SPage ;
typedef  TYPE_1__ SPDBInfoStream ;
typedef  TYPE_1__ SDbiStream ;
typedef  TYPE_1__ R_PDB_STREAM ;
typedef  TYPE_1__ R_PDB7_ROOT_STREAM ;
typedef  TYPE_8__ R_PDB ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  find_indx_in_list (scalar_t__,int,TYPE_1__**) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_pdb_stream (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (scalar_t__) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void finish_pdb_parse(R_PDB *pdb) {
	R_PDB7_ROOT_STREAM *p = pdb->root_stream;
	RListIter *it;
	SPage *page = 0;

	if (!p) {
		return;
	}
	it = r_list_iterator (p->streams_list);
	while (r_list_iter_next (it)) {
		page = (SPage *) r_list_iter_get (it);
		free (page->stream_pages);
		page->stream_pages = 0;
		free (page);
		page = 0;
	}
	r_list_free (p->streams_list);
	p->streams_list = 0;
	free (p);
	p = 0;
	// end of free of R_PDB7_ROOT_STREAM

	// TODO: maybe create some kind of destructor?
	// free of pdb->pdb_streams
// SParsedPDBStream *parsed_pdb_stream = 0;
	SPDBInfoStream *pdb_info_stream = 0;
	STpiStream *tpi_stream = 0;
	SDbiStream *dbi_stream = 0;
	SStreamParseFunc *stream_parse_func;
	R_PDB_STREAM *pdb_stream = 0;
	int i = 0;
#if 1
/* r_list_free should be enough, all the items in a list should be freeable using a generic destructor
   hacking up things like that may only produce problems. so it is better to not assume that a specific
   element in a list is of a specific type and just store this info in the type struct or so.
*/
// XXX: this loop is fucked up. i prefer to leak than crash
	it = r_list_iterator (pdb->pdb_streams);
	while (r_list_iter_next (it)) {
		switch (i) {
		case 1:
			pdb_info_stream = (SPDBInfoStream *) r_list_iter_get (it);
			free_pdb_stream (pdb_info_stream);
			free (pdb_info_stream);
			break;
		case 2:
			tpi_stream = (STpiStream *) r_list_iter_get (it);
			free_pdb_stream (tpi_stream);
			free (tpi_stream);
			break;
		case 3:
			dbi_stream = (SDbiStream *) r_list_iter_get (it);
			free_pdb_stream (dbi_stream);
			free (dbi_stream);
			break;
		default:
			find_indx_in_list (pdb->pdb_streams2, i, &stream_parse_func);
			if (stream_parse_func) {
				break;
			}
			pdb_stream = (R_PDB_STREAM *) r_list_iter_get (it);
			free_pdb_stream (pdb_stream);
			free (pdb_stream);
			break;
		}
		i++;
	}
#endif
	r_list_free (pdb->pdb_streams);
	// enf of free of pdb->pdb_streams

#if 1
	// start of free pdb->pdb_streams2
	it = r_list_iterator (pdb->pdb_streams2);
	while (r_list_iter_next (it)) {
		stream_parse_func = (SStreamParseFunc *) r_list_iter_get (it);
		if (stream_parse_func->free) {
			stream_parse_func->free (stream_parse_func->stream);
			free (stream_parse_func->stream);
		}
		free (stream_parse_func);
	}
#endif
	r_list_free (pdb->pdb_streams2);
	// end of free pdb->streams2

	free (pdb->stream_map);
	r_buf_free (pdb->buf);

// fclose(pdb->fp);
// printf("finish_pdb_parse()\n");
}