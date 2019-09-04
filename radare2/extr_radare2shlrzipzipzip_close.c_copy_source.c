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
typedef  scalar_t__ zip_int64_t ;
struct zip_source {int dummy; } ;
struct zip {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  ZIP_ER_WRITE ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_error_set_from_source (int /*<<< orphan*/ *,struct zip_source*) ; 
 int /*<<< orphan*/  errno ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_source_close (struct zip_source*) ; 
 scalar_t__ zip_source_open (struct zip_source*) ; 
 scalar_t__ zip_source_read (struct zip_source*,char*,int) ; 

__attribute__((used)) static int
copy_source(struct zip *za, struct zip_source *src, FILE *ft)
{
    char buf[BUFSIZE];
    zip_int64_t n;
    int ret;

    if (zip_source_open(src) < 0) {
	_zip_error_set_from_source(&za->error, src);
	return -1;
    }

    ret = 0;
    while ((n=zip_source_read(src, buf, sizeof(buf))) > 0) {
	if (fwrite(buf, 1, (size_t)n, ft) != (size_t)n) {
	    _zip_error_set(&za->error, ZIP_ER_WRITE, errno);
	    ret = -1;
	    break;
	}
    }

    if (n < 0) {
	if (ret == 0)
	    _zip_error_set_from_source(&za->error, src);
	ret = -1;
    }	

    zip_source_close(src);

    return ret;
}