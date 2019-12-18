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
struct TYPE_2__ {scalar_t__ tls_client; scalar_t__ tls_server; scalar_t__ shared_secret_file; } ;
struct context {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_init_crypto_none (struct context*) ; 
 int /*<<< orphan*/  do_init_crypto_static (struct context*,unsigned int const) ; 
 int /*<<< orphan*/  do_init_crypto_tls (struct context*,unsigned int const) ; 

__attribute__((used)) static void
do_init_crypto(struct context *c, const unsigned int flags)
{
    if (c->options.shared_secret_file)
    {
        do_init_crypto_static(c, flags);
    }
    else if (c->options.tls_server || c->options.tls_client)
    {
        do_init_crypto_tls(c, flags);
    }
    else                        /* no encryption or authentication. */
    {
        do_init_crypto_none(c);
    }
}