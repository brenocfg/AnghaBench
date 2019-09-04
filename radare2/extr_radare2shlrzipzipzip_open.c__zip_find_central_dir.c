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
typedef  int zip_int64_t ;
struct zip_error {int dummy; } ;
struct zip_cdir {int dummy; } ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t CDBUFSIZE ; 
 scalar_t__ EFBIG ; 
 int EOCD64LOCLEN ; 
 int EOCDLEN ; 
 scalar_t__ EOCD_MAGIC ; 
 int /*<<< orphan*/  SEEK_END ; 
 unsigned int ZIP_CHECKCONS ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  ZIP_ER_NOZIP ; 
 int /*<<< orphan*/  ZIP_ER_READ ; 
 int /*<<< orphan*/  ZIP_ER_SEEK ; 
 int /*<<< orphan*/  _zip_cdir_free (struct zip_cdir*) ; 
 int _zip_checkcons (int /*<<< orphan*/ *,struct zip_cdir*,struct zip_error*) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* _zip_memmem (unsigned char*,size_t,unsigned char const*,int) ; 
 struct zip_cdir* _zip_readcdir (int /*<<< orphan*/ *,size_t,unsigned char*,unsigned char*,size_t,unsigned int,struct zip_error*) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int fseeko (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t ftello (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  set_error (int*,struct zip_error*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct zip_cdir *
_zip_find_central_dir(FILE *fp, unsigned int flags, int *zep, off_t len)
{
    struct zip_cdir *cdir, *cdirnew;
    unsigned char *buf, *match;
    off_t buf_offset;
    size_t buflen;
    zip_int64_t a, i;
    zip_int64_t best;
    struct zip_error zerr;

    i = fseeko(fp, -(len < CDBUFSIZE ? len : CDBUFSIZE), SEEK_END);
    if (i == -1 && errno != EFBIG) {
	/* seek before start of file on my machine */
	set_error(zep, NULL, ZIP_ER_SEEK);
	return NULL;
    }
    buf_offset = ftello(fp);
    
    /* 64k is too much for stack */
    if ((buf=(unsigned char *)malloc(CDBUFSIZE)) == NULL) {
	set_error(zep, NULL, ZIP_ER_MEMORY);
	return NULL;
    }

    clearerr(fp);
    buflen = fread(buf, 1, CDBUFSIZE, fp);

    if (ferror(fp)) {
	set_error(zep, NULL, ZIP_ER_READ);
	free(buf);
	return NULL;
    }
    
    best = -1;
    cdir = NULL;
    match = buf+ (buflen < CDBUFSIZE ? 0 : EOCD64LOCLEN);
    _zip_error_set(&zerr, ZIP_ER_NOZIP, 0);

    while ((match=_zip_memmem(match, buflen-(size_t)(match-buf)-(EOCDLEN-4),
			      (const unsigned char *)EOCD_MAGIC, 4))!=NULL) {
	/* found match -- check, if good */
	/* to avoid finding the same match all over again */
	match++;
	if ((cdirnew=_zip_readcdir(fp, buf_offset, buf, match-1, buflen, flags,
				   &zerr)) == NULL)
	    continue;

	if (cdir) {
	    if (best <= 0)
		best = _zip_checkcons(fp, cdir, &zerr);
	    a = _zip_checkcons(fp, cdirnew, &zerr);
	    if (best < a) {
		_zip_cdir_free(cdir);
		cdir = cdirnew;
		best = a;
	    }
	    else
		_zip_cdir_free(cdirnew);
	}
	else {
	    cdir = cdirnew;
	    if (flags & ZIP_CHECKCONS)
		best = _zip_checkcons(fp, cdir, &zerr);
	    else
		best = 0;
	}
	cdirnew = NULL;
    }

    free(buf);
    
    if (best < 0) {
	set_error(zep, &zerr, 0);
	_zip_cdir_free(cdir);
	return NULL;
    }

    return cdir;
}