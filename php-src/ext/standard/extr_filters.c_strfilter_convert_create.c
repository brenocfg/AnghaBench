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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  php_stream_filter ;
typedef  int /*<<< orphan*/  php_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ IS_ARRAY ; 
 int PHP_CONV_BASE64_DECODE ; 
 int PHP_CONV_BASE64_ENCODE ; 
 int PHP_CONV_QPRINT_DECODE ; 
 int PHP_CONV_QPRINT_ENCODE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pefree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pemalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ php_convert_filter_ctor (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * php_stream_filter_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strfilter_convert_ops ; 

__attribute__((used)) static php_stream_filter *strfilter_convert_create(const char *filtername, zval *filterparams, uint8_t persistent)
{
	php_convert_filter *inst;
	php_stream_filter *retval = NULL;

	char *dot;
	int conv_mode = 0;

	if (filterparams != NULL && Z_TYPE_P(filterparams) != IS_ARRAY) {
		php_error_docref(NULL, E_WARNING, "stream filter (%s): invalid filter parameter", filtername);
		return NULL;
	}

	if ((dot = strchr(filtername, '.')) == NULL) {
		return NULL;
	}
	++dot;

	inst = pemalloc(sizeof(php_convert_filter), persistent);

	if (strcasecmp(dot, "base64-encode") == 0) {
		conv_mode = PHP_CONV_BASE64_ENCODE;
	} else if (strcasecmp(dot, "base64-decode") == 0) {
		conv_mode = PHP_CONV_BASE64_DECODE;
	} else if (strcasecmp(dot, "quoted-printable-encode") == 0) {
		conv_mode = PHP_CONV_QPRINT_ENCODE;
	} else if (strcasecmp(dot, "quoted-printable-decode") == 0) {
		conv_mode = PHP_CONV_QPRINT_DECODE;
	}

	if (php_convert_filter_ctor(inst, conv_mode,
		(filterparams != NULL ? Z_ARRVAL_P(filterparams) : NULL),
		filtername, persistent) != SUCCESS) {
		goto out;
	}

	retval = php_stream_filter_alloc(&strfilter_convert_ops, inst, persistent);
out:
	if (retval == NULL) {
		pefree(inst, persistent);
	}

	return retval;
}