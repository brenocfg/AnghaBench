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
struct TYPE_2__ {scalar_t__ mssfix_default; } ;
struct options {scalar_t__ proto_force; char* tls_auth_file_inline; char* tls_crypt_inline; int /*<<< orphan*/  gc; scalar_t__ persist_key; int /*<<< orphan*/  tls_crypt_v2_inline; scalar_t__ tls_crypt_v2_file; void* tls_crypt_file; int /*<<< orphan*/  key_direction; void* tls_auth_file; TYPE_1__ ce; scalar_t__ client; scalar_t__ server_bridge_proxy_dhcp; scalar_t__ server_bridge_defined; scalar_t__ server_defined; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  dev; } ;
struct connection_entry {scalar_t__ proto; int bind_local; scalar_t__ af; int tun_mtu_defined; int tun_mtu_extra_defined; char* tls_auth_file_inline; char* tls_crypt_inline; void* tls_crypt_file; void* tls_auth_file; int /*<<< orphan*/  tls_crypt_v2_inline; scalar_t__ tls_crypt_v2_file; int /*<<< orphan*/  key_direction; int /*<<< orphan*/  tun_mtu_extra; int /*<<< orphan*/  link_mtu_defined; scalar_t__ socks_proxy_server; scalar_t__ fragment; scalar_t__ mssfix; int /*<<< orphan*/  flags; int /*<<< orphan*/ * local_port; int /*<<< orphan*/  bind_defined; int /*<<< orphan*/  local_port_defined; int /*<<< orphan*/  local; } ;
struct buffer {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CE_DISABLED ; 
 int const DEV_TYPE_TAP ; 
 void* INLINE_FILE_TAG ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_USAGE ; 
 scalar_t__ PROTO_TCP ; 
 scalar_t__ PROTO_TCP_CLIENT ; 
 scalar_t__ PROTO_TCP_SERVER ; 
 scalar_t__ PROTO_UDP ; 
 int /*<<< orphan*/  TAP_MTU_EXTRA_DEFAULT ; 
 int /*<<< orphan*/  buf_valid (struct buffer*) ; 
 struct buffer buffer_read_from_file (void*,int /*<<< orphan*/ *) ; 
 int dev_type_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ proto_is_udp (scalar_t__) ; 

__attribute__((used)) static void
options_postprocess_mutate_ce(struct options *o, struct connection_entry *ce)
{
    const int dev = dev_type_enum(o->dev, o->dev_type);

#if P2MP_SERVER
    if (o->server_defined || o->server_bridge_defined || o->server_bridge_proxy_dhcp)
    {
        if (ce->proto == PROTO_TCP)
        {
            ce->proto = PROTO_TCP_SERVER;
        }
    }
#endif
#if P2MP
    if (o->client)
    {
        if (ce->proto == PROTO_TCP)
        {
            ce->proto = PROTO_TCP_CLIENT;
        }
    }
#endif

    if (ce->proto == PROTO_TCP_CLIENT && !ce->local && !ce->local_port_defined && !ce->bind_defined)
    {
        ce->bind_local = false;
    }

    if (ce->proto == PROTO_UDP && ce->socks_proxy_server && !ce->local && !ce->local_port_defined && !ce->bind_defined)
    {
        ce->bind_local = false;
    }

    if (!ce->bind_local)
    {
        ce->local_port = NULL;
    }

    /* if protocol forcing is enabled, disable all protocols except for the forced one */
    if (o->proto_force >= 0 && o->proto_force != ce->proto)
    {
        ce->flags |= CE_DISABLED;
    }

    /*
     * If --mssfix is supplied without a parameter, default
     * it to --fragment value, if --fragment is specified.
     */
    if (o->ce.mssfix_default)
    {
#ifdef ENABLE_FRAGMENT
        if (ce->fragment)
        {
            ce->mssfix = ce->fragment;
        }
#else
        msg(M_USAGE, "--mssfix must specify a parameter");
#endif
    }

    /* our socks code is not fully IPv6 enabled yet (TCP works, UDP not)
     * so fall back to IPv4-only (trac #1221)
     */
    if (ce->socks_proxy_server && proto_is_udp(ce->proto) && ce->af != AF_INET)
    {
        if (ce->af == AF_INET6)
        {
            msg(M_INFO, "WARNING: '--proto udp6' is not compatible with "
                "'--socks-proxy' today.  Forcing IPv4 mode." );
        }
        else
        {
            msg(M_INFO, "NOTICE: dual-stack mode for '--proto udp' does not "
                "work correctly with '--socks-proxy' today.  Forcing IPv4." );
        }
        ce->af = AF_INET;
    }

    /*
     * Set MTU defaults
     */
    {
        if (!ce->tun_mtu_defined && !ce->link_mtu_defined)
        {
            ce->tun_mtu_defined = true;
        }
        if ((dev == DEV_TYPE_TAP) && !ce->tun_mtu_extra_defined)
        {
            ce->tun_mtu_extra_defined = true;
            ce->tun_mtu_extra = TAP_MTU_EXTRA_DEFAULT;
        }
    }

    /*
     * Set per-connection block tls-auth/crypt/crypto-v2 fields if undefined.
     *
     * At the end only one of these will be really set because the parser
     * logic prevents configurations where more are set.
     */
    if (!ce->tls_auth_file && !ce->tls_crypt_file && !ce->tls_crypt_v2_file)
    {
        ce->tls_auth_file = o->tls_auth_file;
        ce->tls_auth_file_inline = o->tls_auth_file_inline;
        ce->key_direction = o->key_direction;

        ce->tls_crypt_file = o->tls_crypt_file;
        ce->tls_crypt_inline = o->tls_crypt_inline;

        ce->tls_crypt_v2_file = o->tls_crypt_v2_file;
        ce->tls_crypt_v2_inline = o->tls_crypt_v2_inline;
    }

    /* pre-cache tls-auth/crypt key file if persist-key was specified and keys
     * were not already embedded in the config file
     */
    if (o->persist_key)
    {
        if (ce->tls_auth_file && !ce->tls_auth_file_inline)
        {
            struct buffer in = buffer_read_from_file(ce->tls_auth_file, &o->gc);
            if (!buf_valid(&in))
            {
                msg(M_FATAL, "Cannot pre-load tls-auth keyfile (%s)",
                    ce->tls_auth_file);
            }

            ce->tls_auth_file = INLINE_FILE_TAG;
            ce->tls_auth_file_inline = (char *)in.data;
        }

        if (ce->tls_crypt_file && !ce->tls_crypt_inline)
        {
            struct buffer in = buffer_read_from_file(ce->tls_crypt_file, &o->gc);
            if (!buf_valid(&in))
            {
                msg(M_FATAL, "Cannot pre-load tls-crypt keyfile (%s)",
                    ce->tls_crypt_file);
            }

            ce->tls_crypt_file = INLINE_FILE_TAG;
            ce->tls_crypt_inline = (char *)in.data;
        }
    }
}