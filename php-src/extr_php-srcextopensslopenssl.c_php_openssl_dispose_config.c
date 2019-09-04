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
struct php_x509_request {int /*<<< orphan*/ * req_config; int /*<<< orphan*/ * global_config; int /*<<< orphan*/ * priv_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_openssl_dispose_config(struct php_x509_request * req) /* {{{ */
{
	if (req->priv_key) {
		EVP_PKEY_free(req->priv_key);
		req->priv_key = NULL;
	}
	if (req->global_config) {
		CONF_free(req->global_config);
		req->global_config = NULL;
	}
	if (req->req_config) {
		CONF_free(req->req_config);
		req->req_config = NULL;
	}
}