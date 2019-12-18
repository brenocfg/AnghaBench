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
typedef  int /*<<< orphan*/  zip_uint64_t ;
typedef  int zip_int64_t ;
struct zip_stat {int dummy; } ;
struct zip_source {int dummy; } ;
struct zip {int /*<<< orphan*/  error; } ;
struct read_file {int len; int closep; int /*<<< orphan*/  st; int /*<<< orphan*/ * fname; int /*<<< orphan*/  off; int /*<<< orphan*/ * f; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct read_file*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct zip_stat const*,int) ; 
 int /*<<< orphan*/  read_file ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 struct zip_source* zip_source_function (struct zip*,int /*<<< orphan*/ ,struct read_file*) ; 
 int /*<<< orphan*/  zip_stat_init (int /*<<< orphan*/ *) ; 

struct zip_source *
_zip_source_file_or_p(struct zip *za, const char *fname, FILE *file,
		      zip_uint64_t start, zip_int64_t len, int closep,
		      const struct zip_stat *st)
{
    struct read_file *f;
    struct zip_source *zs;

    if (file == NULL && fname == NULL) {
	_zip_error_set(&za->error, ZIP_ER_INVAL, 0);
	return NULL;
    }

    if ((f=(struct read_file *)malloc(sizeof(struct read_file))) == NULL) {
	_zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    f->fname = NULL;
    if (fname) {
	if ((f->fname=strdup(fname)) == NULL) {
	    _zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
	    free(f);
	    return NULL;
	}
    }
    f->f = file;
    f->off = start;
    f->len = (len ? len : -1);
    f->closep = f->fname ? 1 : closep;
    if (st)
	memcpy(&f->st, st, sizeof(f->st));
    else
	zip_stat_init(&f->st);

    if ((zs=zip_source_function(za, read_file, f)) == NULL) {
	free(f);
	return NULL;
    }

    return zs;
}