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
struct TYPE_4__ {int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ php_url ;
typedef  int /*<<< orphan*/  php_stream_wrapper ;
typedef  int /*<<< orphan*/  php_stream_context ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int GET_FTP_RESULT (int /*<<< orphan*/ *) ; 
 int PHP_STREAM_MKDIR_RECURSIVE ; 
 int REPORT_ERRORS ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrndup (char*,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * php_ftp_fopen_connect (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  php_url_free (TYPE_1__*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int php_stream_ftp_mkdir(php_stream_wrapper *wrapper, const char *url, int mode, int options, php_stream_context *context)
{
	php_stream *stream = NULL;
	php_url *resource = NULL;
	int result, recursive = options & PHP_STREAM_MKDIR_RECURSIVE;
	char tmp_line[512];

	stream = php_ftp_fopen_connect(wrapper, url, "r", 0, NULL, context, NULL, &resource, NULL, NULL);
	if (!stream) {
		if (options & REPORT_ERRORS) {
			php_error_docref(NULL, E_WARNING, "Unable to connect to %s", url);
		}
		goto mkdir_errexit;
	}

	if (resource->path == NULL) {
		if (options & REPORT_ERRORS) {
			php_error_docref(NULL, E_WARNING, "Invalid path provided in %s", url);
		}
		goto mkdir_errexit;
	}

	if (!recursive) {
		php_stream_printf(stream, "MKD %s\r\n", ZSTR_VAL(resource->path));
		result = GET_FTP_RESULT(stream);
    } else {
        /* we look for directory separator from the end of string, thus hopefully reducing our work load */
        char *p, *e, *buf;

        buf = estrndup(ZSTR_VAL(resource->path), ZSTR_LEN(resource->path));
        e = buf + ZSTR_LEN(resource->path);

        /* find a top level directory we need to create */
        while ((p = strrchr(buf, '/'))) {
			*p = '\0';
			php_stream_printf(stream, "CWD %s\r\n", strlen(buf) ? buf : "/");
			result = GET_FTP_RESULT(stream);
			if (result >= 200 && result <= 299) {
				*p = '/';
				break;
			}
		}

		php_stream_printf(stream, "MKD %s\r\n", strlen(buf) ? buf : "/");
		result = GET_FTP_RESULT(stream);

		if (result >= 200 && result <= 299) {
			if (!p) {
				p = buf;
			}
			/* create any needed directories if the creation of the 1st directory worked */
			while (p != e) {
				if (*p == '\0' && *(p + 1) != '\0') {
					*p = '/';
					php_stream_printf(stream, "MKD %s\r\n", buf);
					result = GET_FTP_RESULT(stream);
					if (result < 200 || result > 299) {
						if (options & REPORT_ERRORS) {
							php_error_docref(NULL, E_WARNING, "%s", tmp_line);
						}
						break;
					}
				}
				++p;
			}
		}

		efree(buf);
    }

	php_url_free(resource);
	php_stream_close(stream);

	if (result < 200 || result > 299) {
		/* Failure */
		return 0;
	}

	return 1;

mkdir_errexit:
	if (resource) {
		php_url_free(resource);
	}
	if (stream) {
		php_stream_close(stream);
	}
	return 0;
}