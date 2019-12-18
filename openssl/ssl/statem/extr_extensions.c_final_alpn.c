#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ early_data_ok; } ;
struct TYPE_11__ {int /*<<< orphan*/  server; TYPE_3__ ext; TYPE_2__* session; } ;
struct TYPE_8__ {int /*<<< orphan*/ * alpn_selected; } ;
struct TYPE_9__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_4__*) ; 
 int tls_handle_alpn (TYPE_4__*) ; 

__attribute__((used)) static int final_alpn(SSL *s, unsigned int context, int sent)
{
    if (!s->server && !sent && s->session->ext.alpn_selected != NULL)
            s->ext.early_data_ok = 0;

    if (!s->server || !SSL_IS_TLS13(s))
        return 1;

    /*
     * Call alpn_select callback if needed.  Has to be done after SNI and
     * cipher negotiation (HTTP/2 restricts permitted ciphers). In TLSv1.3
     * we also have to do this before we decide whether to accept early_data.
     * In TLSv1.3 we've already negotiated our cipher so we do this call now.
     * For < TLSv1.3 we defer it until after cipher negotiation.
     *
     * On failure SSLfatal() already called.
     */
    return tls_handle_alpn(s);
}