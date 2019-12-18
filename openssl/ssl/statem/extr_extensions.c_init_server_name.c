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
struct TYPE_4__ {int /*<<< orphan*/ * hostname; } ;
struct TYPE_5__ {TYPE_1__ ext; scalar_t__ servername_done; scalar_t__ server; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_server_name(SSL *s, unsigned int context)
{
    if (s->server) {
        s->servername_done = 0;

        OPENSSL_free(s->ext.hostname);
        s->ext.hostname = NULL;
    }

    return 1;
}