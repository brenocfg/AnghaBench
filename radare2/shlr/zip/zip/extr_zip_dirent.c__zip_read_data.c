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
typedef  char zip_uint8_t ;
struct zip_error {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_INCONS ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  ZIP_ER_READ ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

zip_uint8_t *
_zip_read_data(const zip_uint8_t **buf, FILE *fp, size_t len, int nulp, struct zip_error *error)
{
    zip_uint8_t *r;

    if (len == 0 && nulp == 0)
	return NULL;

    r = (zip_uint8_t *)malloc(nulp ? len+1 : len);
    if (!r) {
	_zip_error_set(error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    if (buf) {
	memcpy(r, *buf, len);
	*buf += len;
    }
    else {
	if (fread(r, 1, len, fp)<len) {
	    free(r);
            if (ferror(fp))
                _zip_error_set(error, ZIP_ER_READ, errno);
            else
                _zip_error_set(error, ZIP_ER_INCONS, 0);
	    return NULL;
	}
    }

    if (nulp) {
	zip_uint8_t *o;
	/* replace any in-string NUL characters with spaces */
	r[len] = 0;
	for (o=r; o<r+len; o++)
	    if (*o == '\0')
		*o = ' ';
    }

    return r;
}