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
struct zip_error {int zip_err; char* str; int /*<<< orphan*/  sys_err; } ;

/* Variables and functions */
 size_t ZIP_ER_MEMORY ; 
#define  ZIP_ET_SYS 129 
#define  ZIP_ET_ZLIB 128 
 char const** _zip_err_str ; 
 int* _zip_err_type ; 
 int /*<<< orphan*/  _zip_error_fini (struct zip_error*) ; 
 int _zip_nerr_str ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 char* zError (int /*<<< orphan*/ ) ; 

const char *
_zip_error_strerror(struct zip_error *err)
{
    const char *zs, *ss;
    char buf[128], *s;

    _zip_error_fini(err);

    if (err->zip_err < 0 || err->zip_err >= _zip_nerr_str) {
	sprintf(buf, "Unknown error %d", err->zip_err);
	zs = NULL;
	ss = buf;
    }
    else {
	zs = _zip_err_str[err->zip_err];
	
	switch (_zip_err_type[err->zip_err]) {
	case ZIP_ET_SYS:
	    ss = strerror(err->sys_err);
	    break;

	case ZIP_ET_ZLIB:
	    ss = zError(err->sys_err);
	    break;

	default:
	    ss = NULL;
	}
    }

    if (ss == NULL)
	return zs;
    else {
	if ((s=(char *)malloc(strlen(ss)
			      + (zs ? strlen(zs)+2 : 0) + 1)) == NULL)
	    return _zip_err_str[ZIP_ER_MEMORY];
	
	sprintf(s, "%s%s%s",
		(zs ? zs : ""),
		(zs ? ": " : ""),
		ss);
	err->str = s;

	return s;
    }
}