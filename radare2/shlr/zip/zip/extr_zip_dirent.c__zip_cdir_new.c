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
typedef  int zip_uint64_t ;
struct zip_error {int dummy; } ;
struct zip_entry {int dummy; } ;
struct zip_cdir {int nentry; int nentry_alloc; int /*<<< orphan*/ * comment; scalar_t__ offset; scalar_t__ size; struct zip_entry* entry; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_entry_init (struct zip_entry*) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct zip_cdir*) ; 
 scalar_t__ malloc (int) ; 

struct zip_cdir *
_zip_cdir_new(zip_uint64_t nentry, struct zip_error *error)
{
    struct zip_cdir *cd;
    zip_uint64_t i;
    
    if ((cd=(struct zip_cdir *)malloc(sizeof(*cd))) == NULL) {
	_zip_error_set(error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    if (nentry == 0) {
	cd->entry = NULL;
    } else if ((nentry > SIZE_MAX/sizeof(*(cd->entry))) || (cd->entry=(struct zip_entry *)malloc(sizeof(*(cd->entry))*(size_t)nentry)) == NULL) {
	_zip_error_set(error, ZIP_ER_MEMORY, 0);
	free(cd);
	return NULL;
    }

    for (i=0; i<nentry; i++)
	_zip_entry_init(cd->entry+i);

    cd->nentry = cd->nentry_alloc = nentry;
    cd->size = cd->offset = 0;
    cd->comment = NULL;

    return cd;
}