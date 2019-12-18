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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_net_4 (int /*<<< orphan*/ *,unsigned long*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_add_custom_ext (int /*<<< orphan*/ *,unsigned int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_add_server_custom_ext (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int SSL_SERVERINFOV1 ; 
 unsigned int SSL_SERVERINFOV2 ; 
 unsigned long SYNTHV1CONTEXT ; 
 int /*<<< orphan*/  serverinfo_srv_add_cb ; 
 int /*<<< orphan*/  serverinfo_srv_parse_cb ; 
 int /*<<< orphan*/  serverinfoex_srv_add_cb ; 
 int /*<<< orphan*/  serverinfoex_srv_parse_cb ; 

__attribute__((used)) static int serverinfo_process_buffer(unsigned int version,
                                     const unsigned char *serverinfo,
                                     size_t serverinfo_length, SSL_CTX *ctx)
{
    PACKET pkt;

    if (serverinfo == NULL || serverinfo_length == 0)
        return 0;

    if (version != SSL_SERVERINFOV1 && version != SSL_SERVERINFOV2)
        return 0;

    if (!PACKET_buf_init(&pkt, serverinfo, serverinfo_length))
        return 0;

    while (PACKET_remaining(&pkt)) {
        unsigned long context = 0;
        unsigned int ext_type = 0;
        PACKET data;

        if ((version == SSL_SERVERINFOV2 && !PACKET_get_net_4(&pkt, &context))
                || !PACKET_get_net_2(&pkt, &ext_type)
                || !PACKET_get_length_prefixed_2(&pkt, &data))
            return 0;

        if (ctx == NULL)
            continue;

        /*
         * The old style custom extensions API could be set separately for
         * server/client, i.e. you could set one custom extension for a client,
         * and *for the same extension in the same SSL_CTX* you could set a
         * custom extension for the server as well. It seems quite weird to be
         * setting a custom extension for both client and server in a single
         * SSL_CTX - but theoretically possible. This isn't possible in the
         * new API. Therefore, if we have V1 serverinfo we use the old API. We
         * also use the old API even if we have V2 serverinfo but the context
         * looks like an old style <= TLSv1.2 extension.
         */
        if (version == SSL_SERVERINFOV1 || context == SYNTHV1CONTEXT) {
            if (!SSL_CTX_add_server_custom_ext(ctx, ext_type,
                                               serverinfo_srv_add_cb,
                                               NULL, NULL,
                                               serverinfo_srv_parse_cb,
                                               NULL))
                return 0;
        } else {
            if (!SSL_CTX_add_custom_ext(ctx, ext_type, context,
                                        serverinfoex_srv_add_cb,
                                        NULL, NULL,
                                        serverinfoex_srv_parse_cb,
                                        NULL))
                return 0;
        }
    }

    return 1;
}