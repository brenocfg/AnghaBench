#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  input_filters; } ;
typedef  TYPE_1__ request_rec ;
struct TYPE_5__ {int /*<<< orphan*/ * brigade; TYPE_1__* r; } ;
typedef  TYPE_2__ php_struct ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_bucket_brigade ;

/* Variables and functions */
 int /*<<< orphan*/  APR_BLOCK_READ ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  AP_MODE_READBYTES ; 
 TYPE_2__* SG (int /*<<< orphan*/ ) ; 
 scalar_t__ ap_get_brigade (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  apr_brigade_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_brigade_flatten (int /*<<< orphan*/ *,char*,size_t*) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static apr_size_t
php_apache_sapi_read_post(char *buf, size_t count_bytes)
{
	apr_size_t len, tlen=0;
	php_struct *ctx = SG(server_context);
	request_rec *r;
	apr_bucket_brigade *brigade;

	r = ctx->r;
	brigade = ctx->brigade;
	len = count_bytes;

	/*
	 * This loop is needed because ap_get_brigade() can return us partial data
	 * which would cause premature termination of request read. Therefor we
	 * need to make sure that if data is available we fill the buffer completely.
	 */

	while (ap_get_brigade(r->input_filters, brigade, AP_MODE_READBYTES, APR_BLOCK_READ, len) == APR_SUCCESS) {
		apr_brigade_flatten(brigade, buf, &len);
		apr_brigade_cleanup(brigade);
		tlen += len;
		if (tlen == count_bytes || !len) {
			break;
		}
		buf += len;
		len = count_bytes - tlen;
	}

	return tlen;
}