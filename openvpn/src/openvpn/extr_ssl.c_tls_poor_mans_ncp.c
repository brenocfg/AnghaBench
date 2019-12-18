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
struct options {int /*<<< orphan*/  ciphername; int /*<<< orphan*/  gc; int /*<<< orphan*/  ncp_ciphers; scalar_t__ ncp_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TLS_DEBUG_LOW ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  string_alloc (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_item_in_cipher_list (char const*,int /*<<< orphan*/ ) ; 

void
tls_poor_mans_ncp(struct options *o, const char *remote_ciphername)
{
    if (o->ncp_enabled && remote_ciphername
        && 0 != strcmp(o->ciphername, remote_ciphername))
    {
        if (tls_item_in_cipher_list(remote_ciphername, o->ncp_ciphers))
        {
            o->ciphername = string_alloc(remote_ciphername, &o->gc);
            msg(D_TLS_DEBUG_LOW, "Using peer cipher '%s'", o->ciphername);
        }
    }
}