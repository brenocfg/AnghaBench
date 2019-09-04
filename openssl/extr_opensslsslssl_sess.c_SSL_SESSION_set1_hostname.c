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
struct TYPE_5__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 

int SSL_SESSION_set1_hostname(SSL_SESSION *s, const char *hostname)
{
    OPENSSL_free(s->ext.hostname);
    if (hostname == NULL) {
        s->ext.hostname = NULL;
        return 1;
    }
    s->ext.hostname = OPENSSL_strdup(hostname);

    return s->ext.hostname != NULL;
}