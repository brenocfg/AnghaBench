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
typedef  int /*<<< orphan*/  request_rec ;
struct TYPE_4__ {TYPE_2__* r; } ;
typedef  TYPE_1__ php_struct ;
struct TYPE_5__ {int /*<<< orphan*/  output_filters; } ;

/* Variables and functions */
 TYPE_1__* SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ap_sub_req_lookup_uri (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_context ; 

__attribute__((used)) static request_rec *php_apache_lookup_uri(char *filename)
{
	php_struct *ctx = SG(server_context);

	if (!filename || !ctx || !ctx->r) {
		return NULL;
	}

	return ap_sub_req_lookup_uri(filename, ctx->r, ctx->r->output_filters);
}