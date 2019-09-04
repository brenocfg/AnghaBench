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
struct zip_file {int /*<<< orphan*/ * src; scalar_t__ eof; int /*<<< orphan*/  error; struct zip* za; } ;
struct zip {scalar_t__ nfile; scalar_t__ nfile_alloc; struct zip_file** file; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct zip_file*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (struct zip_file**,unsigned int) ; 

__attribute__((used)) static struct zip_file *
_zip_file_new(struct zip *za)
{
    struct zip_file *zf, **file;

    if ((zf=(struct zip_file *)malloc(sizeof(struct zip_file))) == NULL) {
	_zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
	return NULL;
    }
    
    if (za->nfile+1 >= za->nfile_alloc) {
	unsigned int n;
	n = za->nfile_alloc + 10;
	file = (struct zip_file **)realloc(za->file,
					   n*sizeof(struct zip_file *));
	if (file == NULL) {
	    _zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
	    free(zf);
	    return NULL;
	}
	za->nfile_alloc = n;
	za->file = file;
    }

    za->file[za->nfile++] = zf;

    zf->za = za;
    _zip_error_init(&zf->error);
    zf->eof = 0;
    zf->src = NULL;

    return zf;
}