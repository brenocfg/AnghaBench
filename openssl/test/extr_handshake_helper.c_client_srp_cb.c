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
struct TYPE_2__ {int /*<<< orphan*/  srp_password; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ CTX_DATA ;

/* Variables and functions */
 char* OPENSSL_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *client_srp_cb(SSL *s, void *arg)
{
    CTX_DATA *ctx_data = (CTX_DATA*)(arg);
    return OPENSSL_strdup(ctx_data->srp_password);
}