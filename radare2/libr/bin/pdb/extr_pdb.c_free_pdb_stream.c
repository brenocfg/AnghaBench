#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pages; } ;
typedef  TYPE_1__ R_PDB_STREAM ;

/* Variables and functions */

__attribute__((used)) static void free_pdb_stream(void *stream) {
	R_PDB_STREAM *pdb_stream = (R_PDB_STREAM *) stream;
	if (pdb_stream) {
		// R_FREE (pdb_stream->pages);
		if (pdb_stream->pages) {
// free(pdb_stream->pages);
			pdb_stream->pages = 0;
		}
	}
}