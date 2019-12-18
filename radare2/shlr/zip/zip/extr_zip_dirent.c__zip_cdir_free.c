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
typedef  scalar_t__ zip_uint64_t ;
struct zip_cdir {scalar_t__ nentry; scalar_t__ entry; int /*<<< orphan*/  comment; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zip_entry_finalize (scalar_t__) ; 
 int /*<<< orphan*/  _zip_string_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct zip_cdir*) ; 

void
_zip_cdir_free(struct zip_cdir *cd)
{
    zip_uint64_t i;

    if (!cd)
	return;

    for (i=0; i<cd->nentry; i++)
	_zip_entry_finalize(cd->entry+i);
    free(cd->entry);
    _zip_string_free(cd->comment);
    free(cd);
}