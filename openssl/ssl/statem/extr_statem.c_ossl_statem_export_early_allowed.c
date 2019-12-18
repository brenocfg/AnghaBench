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
struct TYPE_4__ {scalar_t__ early_data; } ;
struct TYPE_5__ {TYPE_1__ ext; int /*<<< orphan*/  server; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 scalar_t__ SSL_EARLY_DATA_ACCEPTED ; 
 scalar_t__ SSL_EARLY_DATA_NOT_SENT ; 

int ossl_statem_export_early_allowed(SSL *s)
{
    /*
     * The early exporter secret is only present on the server if we
     * have accepted early_data. It is present on the client as long
     * as we have sent early_data.
     */
    return s->ext.early_data == SSL_EARLY_DATA_ACCEPTED
           || (!s->server && s->ext.early_data != SSL_EARLY_DATA_NOT_SENT);
}