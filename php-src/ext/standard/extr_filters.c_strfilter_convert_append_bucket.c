#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream_filter ;
typedef  int /*<<< orphan*/  php_stream_bucket_brigade ;
typedef  int /*<<< orphan*/  php_stream_bucket ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_3__ {size_t stub_len; char* stub; int /*<<< orphan*/  filtername; int /*<<< orphan*/  cd; } ;
typedef  TYPE_1__ php_convert_filter ;
typedef  int php_conv_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
#define  PHP_CONV_ERR_INVALID_SEQ 132 
#define  PHP_CONV_ERR_MORE 131 
#define  PHP_CONV_ERR_TOO_BIG 130 
#define  PHP_CONV_ERR_UNEXPECTED_EOS 129 
#define  PHP_CONV_ERR_UNKNOWN 128 
 int SUCCESS ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 int /*<<< orphan*/  pefree (char*,int) ; 
 char* pemalloc (size_t,int) ; 
 char* perealloc (char*,size_t,int) ; 
 int php_conv_convert (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_bucket_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_bucket_new (int /*<<< orphan*/ *,char*,size_t,int,int) ; 

__attribute__((used)) static int strfilter_convert_append_bucket(
		php_convert_filter *inst,
		php_stream *stream, php_stream_filter *filter,
		php_stream_bucket_brigade *buckets_out,
		const char *ps, size_t buf_len, size_t *consumed,
		int persistent)
{
	php_conv_err_t err;
	php_stream_bucket *new_bucket;
	char *out_buf = NULL;
	size_t out_buf_size;
	char *pd;
	const char *pt;
	size_t ocnt, icnt, tcnt;
	size_t initial_out_buf_size;

	if (ps == NULL) {
		initial_out_buf_size = 64;
		icnt = 1;
	} else {
		initial_out_buf_size = buf_len;
		icnt = buf_len;
	}

	out_buf_size = ocnt = initial_out_buf_size;
	out_buf = pemalloc(out_buf_size, persistent);

	pd = out_buf;

	if (inst->stub_len > 0) {
		pt = inst->stub;
		tcnt = inst->stub_len;

		while (tcnt > 0) {
			err = php_conv_convert(inst->cd, &pt, &tcnt, &pd, &ocnt);

			switch (err) {
				case PHP_CONV_ERR_INVALID_SEQ:
					php_error_docref(NULL, E_WARNING, "stream filter (%s): invalid byte sequence", inst->filtername);
					goto out_failure;

				case PHP_CONV_ERR_MORE:
					if (ps != NULL) {
						if (icnt > 0) {
							if (inst->stub_len >= sizeof(inst->stub)) {
								php_error_docref(NULL, E_WARNING, "stream filter (%s): insufficient buffer", inst->filtername);
								goto out_failure;
							}
							inst->stub[inst->stub_len++] = *(ps++);
							icnt--;
							pt = inst->stub;
							tcnt = inst->stub_len;
						} else {
							tcnt = 0;
							break;
						}
					}
					break;

				case PHP_CONV_ERR_UNEXPECTED_EOS:
					php_error_docref(NULL, E_WARNING, "stream filter (%s): unexpected end of stream", inst->filtername);
					goto out_failure;

				case PHP_CONV_ERR_TOO_BIG: {
					char *new_out_buf;
					size_t new_out_buf_size;

					new_out_buf_size = out_buf_size << 1;

					if (new_out_buf_size < out_buf_size) {
						/* whoa! no bigger buckets are sold anywhere... */
						if (NULL == (new_bucket = php_stream_bucket_new(stream, out_buf, (out_buf_size - ocnt), 1, persistent))) {
							goto out_failure;
						}

						php_stream_bucket_append(buckets_out, new_bucket);

						out_buf_size = ocnt = initial_out_buf_size;
						out_buf = pemalloc(out_buf_size, persistent);
						pd = out_buf;
					} else {
						new_out_buf = perealloc(out_buf, new_out_buf_size, persistent);
						pd = new_out_buf + (pd - out_buf);
						ocnt += (new_out_buf_size - out_buf_size);
						out_buf = new_out_buf;
						out_buf_size = new_out_buf_size;
					}
				} break;

				case PHP_CONV_ERR_UNKNOWN:
					php_error_docref(NULL, E_WARNING, "stream filter (%s): unknown error", inst->filtername);
					goto out_failure;

				default:
					break;
			}
		}
		memmove(inst->stub, pt, tcnt);
		inst->stub_len = tcnt;
	}

	while (icnt > 0) {
		err = ((ps == NULL ? php_conv_convert(inst->cd, NULL, NULL, &pd, &ocnt):
				php_conv_convert(inst->cd, &ps, &icnt, &pd, &ocnt)));
		switch (err) {
			case PHP_CONV_ERR_INVALID_SEQ:
				php_error_docref(NULL, E_WARNING, "stream filter (%s): invalid byte sequence", inst->filtername);
				goto out_failure;

			case PHP_CONV_ERR_MORE:
				if (ps != NULL) {
					if (icnt > sizeof(inst->stub)) {
						php_error_docref(NULL, E_WARNING, "stream filter (%s): insufficient buffer", inst->filtername);
						goto out_failure;
					}
					memcpy(inst->stub, ps, icnt);
					inst->stub_len = icnt;
					ps += icnt;
					icnt = 0;
				} else {
					php_error_docref(NULL, E_WARNING, "stream filter (%s): unexpected octet values", inst->filtername);
					goto out_failure;
				}
				break;

			case PHP_CONV_ERR_TOO_BIG: {
				char *new_out_buf;
				size_t new_out_buf_size;

				new_out_buf_size = out_buf_size << 1;

				if (new_out_buf_size < out_buf_size) {
					/* whoa! no bigger buckets are sold anywhere... */
					if (NULL == (new_bucket = php_stream_bucket_new(stream, out_buf, (out_buf_size - ocnt), 1, persistent))) {
						goto out_failure;
					}

					php_stream_bucket_append(buckets_out, new_bucket);

					out_buf_size = ocnt = initial_out_buf_size;
					out_buf = pemalloc(out_buf_size, persistent);
					pd = out_buf;
				} else {
					new_out_buf = perealloc(out_buf, new_out_buf_size, persistent);
					pd = new_out_buf + (pd - out_buf);
					ocnt += (new_out_buf_size - out_buf_size);
					out_buf = new_out_buf;
					out_buf_size = new_out_buf_size;
				}
			} break;

			case PHP_CONV_ERR_UNKNOWN:
				php_error_docref(NULL, E_WARNING, "stream filter (%s): unknown error", inst->filtername);
				goto out_failure;

			default:
				if (ps == NULL) {
					icnt = 0;
				}
				break;
		}
	}

	if (out_buf_size > ocnt) {
		if (NULL == (new_bucket = php_stream_bucket_new(stream, out_buf, (out_buf_size - ocnt), 1, persistent))) {
			goto out_failure;
		}
		php_stream_bucket_append(buckets_out, new_bucket);
	} else {
		pefree(out_buf, persistent);
	}
	*consumed += buf_len - icnt;

	return SUCCESS;

out_failure:
	pefree(out_buf, persistent);
	return FAILURE;
}