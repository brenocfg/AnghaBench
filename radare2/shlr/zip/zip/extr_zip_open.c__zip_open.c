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
struct zip_cdir {int /*<<< orphan*/  comment; int /*<<< orphan*/  nentry_alloc; int /*<<< orphan*/  nentry; int /*<<< orphan*/  entry; } ;
struct zip {int /*<<< orphan*/  flags; int /*<<< orphan*/  ch_flags; int /*<<< orphan*/ * zp; int /*<<< orphan*/  comment_orig; int /*<<< orphan*/  nentry_alloc; int /*<<< orphan*/  nentry; int /*<<< orphan*/  entry; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int ZIP_ER_SEEK ; 
 struct zip* _zip_allocate_new (char const*,unsigned int,int*) ; 
 int /*<<< orphan*/  _zip_cdir_free (struct zip_cdir*) ; 
 int /*<<< orphan*/  _zip_check_torrentzip (struct zip*,struct zip_cdir*) ; 
 struct zip_cdir* _zip_find_central_dir (int /*<<< orphan*/ *,unsigned int,int*,scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct zip_cdir*) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 

struct zip *
_zip_open(const char *fn, FILE *fp, unsigned int flags, int *zep)
{
    struct zip *za;
    struct zip_cdir *cdir;
    off_t len;

    if (fseeko(fp, 0, SEEK_END) < 0) {
	*zep = ZIP_ER_SEEK;
	return NULL;
    }
    len = ftello(fp);

    /* treat empty files as empty archives */
    if (len == 0) {
	if ((za=_zip_allocate_new(fn, flags, zep)) == NULL)
	    fclose(fp);
	else
	    za->zp = fp;
	return za;
    }

    cdir = _zip_find_central_dir(fp, flags, zep, len);
    if (cdir == NULL) {
	fclose(fp);
	return NULL;
    }

    if ((za=_zip_allocate_new(fn, flags, zep)) == NULL) {
	_zip_cdir_free(cdir);
	fclose(fp);
	return NULL;
    }

    za->entry = cdir->entry;
    za->nentry = cdir->nentry;
    za->nentry_alloc = cdir->nentry_alloc;
    za->comment_orig = cdir->comment;
    
    za->zp = fp;

    _zip_check_torrentzip(za, cdir);

    za->ch_flags = za->flags;

    free(cdir);

    return za;
}