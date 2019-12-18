#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {scalar_t__ fd; size_t st_size; } ;
typedef  TYPE_1__ ps_files ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 unsigned int UINT_MAX ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int _write (scalar_t__,char*,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ftruncate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  php_ignore_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_files_open (TYPE_1__*,char*) ; 
 size_t pwrite (scalar_t__,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t write (scalar_t__,char*,size_t) ; 

__attribute__((used)) static int ps_files_write(ps_files *data, zend_string *key, zend_string *val)
{
	size_t n = 0;

	/* PS(id) may be changed by calling session_regenerate_id().
	   Re-initialization should be tried here. ps_files_open() checks
       data->lastkey and reopen when it is needed. */
	ps_files_open(data, ZSTR_VAL(key));
	if (data->fd < 0) {
		return FAILURE;
	}

	/* Truncate file if the amount of new data is smaller than the existing data set. */
	if (ZSTR_LEN(val) < data->st_size) {
		php_ignore_value(ftruncate(data->fd, 0));
	}

#if defined(HAVE_PWRITE)
	n = pwrite(data->fd, ZSTR_VAL(val), ZSTR_LEN(val), 0);
#else
	lseek(data->fd, 0, SEEK_SET);
#ifdef PHP_WIN32
	{
		unsigned int to_write = ZSTR_LEN(val) > UINT_MAX ? UINT_MAX : (unsigned int)ZSTR_LEN(val);
		char *buf = ZSTR_VAL(val);
		int wrote;

		do {
			wrote = _write(data->fd, buf, to_write);

			n += wrote;
			buf = wrote > -1 ? buf + wrote : 0;
			to_write = wrote > -1 ? (ZSTR_LEN(val) - n > UINT_MAX ? UINT_MAX : (unsigned int)(ZSTR_LEN(val) - n)): 0;

		} while(wrote > 0);
	}
#else
	n = write(data->fd, ZSTR_VAL(val), ZSTR_LEN(val));
#endif
#endif

	if (n != ZSTR_LEN(val)) {
		if (n == (size_t)-1) {
			php_error_docref(NULL, E_WARNING, "write failed: %s (%d)", strerror(errno), errno);
		} else {
			php_error_docref(NULL, E_WARNING, "write wrote less bytes than requested");
		}
		return FAILURE;
	}

	return SUCCESS;
}