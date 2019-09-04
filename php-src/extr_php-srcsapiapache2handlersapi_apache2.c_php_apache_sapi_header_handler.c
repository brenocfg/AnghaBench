#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sapi_headers_struct ;
struct TYPE_6__ {int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ sapi_header_struct ;
typedef  int sapi_header_op_enum ;
struct TYPE_7__ {TYPE_4__* r; int /*<<< orphan*/  content_type; } ;
typedef  TYPE_2__ php_struct ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_8__ {int /*<<< orphan*/  headers_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
#define  SAPI_HEADER_ADD 131 
#define  SAPI_HEADER_DELETE 130 
#define  SAPI_HEADER_DELETE_ALL 129 
#define  SAPI_HEADER_REPLACE 128 
 TYPE_2__* SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_set_content_length (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_strtoff (int /*<<< orphan*/ *,char*,char**,int) ; 
 int /*<<< orphan*/  apr_table_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  apr_table_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_table_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  apr_table_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 int /*<<< orphan*/  server_context ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static int
php_apache_sapi_header_handler(sapi_header_struct *sapi_header, sapi_header_op_enum op, sapi_headers_struct *sapi_headers)
{
	php_struct *ctx;
	char *val, *ptr;

	ctx = SG(server_context);

	switch (op) {
		case SAPI_HEADER_DELETE:
			apr_table_unset(ctx->r->headers_out, sapi_header->header);
			return 0;

		case SAPI_HEADER_DELETE_ALL:
			apr_table_clear(ctx->r->headers_out);
			return 0;

		case SAPI_HEADER_ADD:
		case SAPI_HEADER_REPLACE:
			val = strchr(sapi_header->header, ':');

			if (!val) {
				return 0;
			}
			ptr = val;

			*val = '\0';

			do {
				val++;
			} while (*val == ' ');

			if (!strcasecmp(sapi_header->header, "content-type")) {
				if (ctx->content_type) {
					efree(ctx->content_type);
				}
				ctx->content_type = estrdup(val);
			} else if (!strcasecmp(sapi_header->header, "content-length")) {
				apr_off_t clen = 0;

				if (APR_SUCCESS != apr_strtoff(&clen, val, (char **) NULL, 10)) {
					/* We'll fall back to strtol, since that's what we used to
					 * do anyway. */
					clen = (apr_off_t) strtol(val, (char **) NULL, 10);
				}

				ap_set_content_length(ctx->r, clen);
			} else if (op == SAPI_HEADER_REPLACE) {
				apr_table_set(ctx->r->headers_out, sapi_header->header, val);
			} else {
				apr_table_add(ctx->r->headers_out, sapi_header->header, val);
			}

			*ptr = ':';

			return SAPI_HEADER_ADD;

		default:
			return 0;
	}
}