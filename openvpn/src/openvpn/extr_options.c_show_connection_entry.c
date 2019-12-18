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
struct connection_entry {int /*<<< orphan*/  key_direction; scalar_t__ http_proxy_options; int /*<<< orphan*/  af; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SHOW_PARMS ; 
 int /*<<< orphan*/  SHOW_BOOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHOW_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHOW_PARM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SHOW_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_defined ; 
 int /*<<< orphan*/  bind_ipv6_only ; 
 int /*<<< orphan*/  bind_local ; 
 int /*<<< orphan*/  connect_retry_seconds ; 
 int /*<<< orphan*/  connect_timeout ; 
 int /*<<< orphan*/  explicit_exit_notification ; 
 int /*<<< orphan*/  fragment ; 
 int /*<<< orphan*/  key_direction ; 
 int /*<<< orphan*/  keydirection2ascii (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  link_mtu ; 
 int /*<<< orphan*/  link_mtu_defined ; 
 int /*<<< orphan*/  local ; 
 int /*<<< orphan*/  local_port ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mssfix ; 
 int /*<<< orphan*/  mtu_discover_type ; 
 int /*<<< orphan*/  proto2ascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remote ; 
 int /*<<< orphan*/  remote_float ; 
 int /*<<< orphan*/  remote_port ; 
 int /*<<< orphan*/  show_http_proxy_options (scalar_t__) ; 
 int /*<<< orphan*/  socks_proxy_port ; 
 int /*<<< orphan*/  socks_proxy_server ; 
 int /*<<< orphan*/  tls_auth_file ; 
 int /*<<< orphan*/  tls_crypt_file ; 
 int /*<<< orphan*/  tls_crypt_v2_file ; 
 int /*<<< orphan*/  tun_mtu ; 
 int /*<<< orphan*/  tun_mtu_defined ; 
 int /*<<< orphan*/  tun_mtu_extra ; 
 int /*<<< orphan*/  tun_mtu_extra_defined ; 

__attribute__((used)) static void
show_connection_entry(const struct connection_entry *o)
{
    msg(D_SHOW_PARMS, "  proto = %s", proto2ascii(o->proto, o->af, false));
    SHOW_STR(local);
    SHOW_STR(local_port);
    SHOW_STR(remote);
    SHOW_STR(remote_port);
    SHOW_BOOL(remote_float);
    SHOW_BOOL(bind_defined);
    SHOW_BOOL(bind_local);
    SHOW_BOOL(bind_ipv6_only);
    SHOW_INT(connect_retry_seconds);
    SHOW_INT(connect_timeout);

    if (o->http_proxy_options)
    {
        show_http_proxy_options(o->http_proxy_options);
    }
    SHOW_STR(socks_proxy_server);
    SHOW_STR(socks_proxy_port);
    SHOW_INT(tun_mtu);
    SHOW_BOOL(tun_mtu_defined);
    SHOW_INT(link_mtu);
    SHOW_BOOL(link_mtu_defined);
    SHOW_INT(tun_mtu_extra);
    SHOW_BOOL(tun_mtu_extra_defined);

    SHOW_INT(mtu_discover_type);

#ifdef ENABLE_FRAGMENT
    SHOW_INT(fragment);
#endif
    SHOW_INT(mssfix);

#ifdef ENABLE_OCC
    SHOW_INT(explicit_exit_notification);
#endif

    SHOW_STR(tls_auth_file);
    SHOW_PARM(key_direction, keydirection2ascii(o->key_direction, false, true),
              "%s");
    SHOW_STR(tls_crypt_file);
    SHOW_STR(tls_crypt_v2_file);
}