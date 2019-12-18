#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  srp_password; int /*<<< orphan*/  srp_user; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ CTX_DATA ;

/* Variables and functions */
 int SSL3_AL_FATAL ; 
 int SSL_AD_INTERNAL_ERROR ; 
 int SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_get_srp_username (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_set_srp_server_param_pw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int server_srp_cb(SSL *s, int *ad, void *arg)
{
    CTX_DATA *ctx_data = (CTX_DATA*)(arg);
    if (strcmp(ctx_data->srp_user, SSL_get_srp_username(s)) != 0)
        return SSL3_AL_FATAL;
    if (SSL_set_srp_server_param_pw(s, ctx_data->srp_user,
                                    ctx_data->srp_password,
                                    "2048" /* known group */) < 0) {
        *ad = SSL_AD_INTERNAL_ERROR;
        return SSL3_AL_FATAL;
    }
    return SSL_ERROR_NONE;
}