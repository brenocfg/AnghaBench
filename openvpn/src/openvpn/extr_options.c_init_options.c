#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int txqueuelen; int dhcp_lease_time; scalar_t__ dhcp_masq_offset; int /*<<< orphan*/  ip_win32_type; } ;
struct TYPE_3__ {int bind_ipv6_only; int connect_retry_seconds; int connect_retry_seconds_max; int connect_timeout; int bind_local; int mtu_discover_type; int /*<<< orphan*/  mssfix; int /*<<< orphan*/  link_mtu; int /*<<< orphan*/  tun_mtu; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; int /*<<< orphan*/  af; int /*<<< orphan*/  proto; } ;
struct options {int gc_owned; int verbosity; int status_file_update_freq; int status_file_version; int route_delay_window; int resolve_in_advance; int proto_force; int occ; int management_log_history_cache; int management_echo_buffer_size; int management_state_buffer_size; int persist_mode; int block_outside_dns; int wintun; int vlan_pvid; int real_hash_size; int virtual_hash_size; int n_bcast_buf; int tcp_queue_limit; int max_clients; int max_routes_per_client; int ifconfig_pool_persist_refresh_freq; int scheduled_exit_interval; char* ciphername; int ncp_enabled; char* ncp_ciphers; char* authname; char* prng_hash; int prng_nonce_secret_len; int replay; int use_prediction_resistance; int key_method; int tls_timeout; int renegotiate_bytes; int renegotiate_seconds; int renegotiate_seconds_min; int handshake_window; int transition_window; int pkcs11_pin_cache_period; int auth_token_generate; char* tmp_dir; int allow_recursive_routing; int /*<<< orphan*/  x509_username_field; int /*<<< orphan*/ * ecdh_curve; int /*<<< orphan*/ * tls_cert_profile; int /*<<< orphan*/  key_direction; int /*<<< orphan*/  replay_time; int /*<<< orphan*/  replay_window; scalar_t__ stale_routes_check_interval; int /*<<< orphan*/  vlan_accept; int /*<<< orphan*/  route_method; TYPE_2__ tuntap_options; int /*<<< orphan*/  resolve_retry_seconds; TYPE_1__ ce; scalar_t__ connect_retry_max; int /*<<< orphan*/  topology; int /*<<< orphan*/  mode; int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  CLEAR (struct options) ; 
 int /*<<< orphan*/  DEFAULT_SEQ_BACKTRACK ; 
 int /*<<< orphan*/  DEFAULT_TIME_BACKTRACK ; 
 int /*<<< orphan*/  IPW32_SET_ADAPTIVE ; 
 int /*<<< orphan*/  IPW32_SET_DHCP_MASQ ; 
 int /*<<< orphan*/  KEY_DIRECTION_BIDIRECTIONAL ; 
 int /*<<< orphan*/  LINK_MTU_DEFAULT ; 
 int /*<<< orphan*/  MODE_POINT_TO_POINT ; 
 int /*<<< orphan*/  MSSFIX_DEFAULT ; 
 int /*<<< orphan*/  OPENVPN_PORT ; 
 int /*<<< orphan*/  PROTO_UDP ; 
 int /*<<< orphan*/  RESOLV_RETRY_INFINITE ; 
 int /*<<< orphan*/  ROUTE_METHOD_ADAPTIVE ; 
 int /*<<< orphan*/  TOP_NET30 ; 
 int /*<<< orphan*/  TUN_MTU_DEFAULT ; 
 int /*<<< orphan*/  VLAN_ALL ; 
 int /*<<< orphan*/  X509_USERNAME_FIELD_DEFAULT ; 
 int /*<<< orphan*/  gc_init (int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 char* win_get_tempdir () ; 

void
init_options(struct options *o, const bool init_gc)
{
    CLEAR(*o);
    if (init_gc)
    {
        gc_init(&o->gc);
        o->gc_owned = true;
    }
    o->mode = MODE_POINT_TO_POINT;
    o->topology = TOP_NET30;
    o->ce.proto = PROTO_UDP;
    o->ce.af = AF_UNSPEC;
    o->ce.bind_ipv6_only = false;
    o->ce.connect_retry_seconds = 5;
    o->ce.connect_retry_seconds_max = 300;
    o->ce.connect_timeout = 120;
    o->connect_retry_max = 0;
    o->ce.local_port = o->ce.remote_port = OPENVPN_PORT;
    o->verbosity = 1;
    o->status_file_update_freq = 60;
    o->status_file_version = 1;
    o->ce.bind_local = true;
    o->ce.tun_mtu = TUN_MTU_DEFAULT;
    o->ce.link_mtu = LINK_MTU_DEFAULT;
    o->ce.mtu_discover_type = -1;
    o->ce.mssfix = MSSFIX_DEFAULT;
    o->route_delay_window = 30;
    o->resolve_retry_seconds = RESOLV_RETRY_INFINITE;
    o->resolve_in_advance = false;
    o->proto_force = -1;
#ifdef ENABLE_OCC
    o->occ = true;
#endif
#ifdef ENABLE_MANAGEMENT
    o->management_log_history_cache = 250;
    o->management_echo_buffer_size = 100;
    o->management_state_buffer_size = 100;
#endif
#ifdef ENABLE_FEATURE_TUN_PERSIST
    o->persist_mode = 1;
#endif
#ifdef TARGET_LINUX
    o->tuntap_options.txqueuelen = 100;
#endif
#ifdef _WIN32
#if 0
    o->tuntap_options.ip_win32_type = IPW32_SET_ADAPTIVE;
#else
    o->tuntap_options.ip_win32_type = IPW32_SET_DHCP_MASQ;
#endif
    o->tuntap_options.dhcp_lease_time = 31536000; /* one year */
    o->tuntap_options.dhcp_masq_offset = 0;     /* use network address as internal DHCP server address */
    o->route_method = ROUTE_METHOD_ADAPTIVE;
    o->block_outside_dns = false;
    o->wintun = false;
#endif
    o->vlan_accept = VLAN_ALL;
    o->vlan_pvid = 1;
#if P2MP_SERVER
    o->real_hash_size = 256;
    o->virtual_hash_size = 256;
    o->n_bcast_buf = 256;
    o->tcp_queue_limit = 64;
    o->max_clients = 1024;
    o->max_routes_per_client = 256;
    o->stale_routes_check_interval = 0;
    o->ifconfig_pool_persist_refresh_freq = 600;
#endif
#if P2MP
    o->scheduled_exit_interval = 5;
#endif
    o->ciphername = "BF-CBC";
#ifdef HAVE_AEAD_CIPHER_MODES /* IV_NCP=2 requires GCM support */
    o->ncp_enabled = true;
#else
    o->ncp_enabled = false;
#endif
    o->ncp_ciphers = "AES-256-GCM:AES-128-GCM";
    o->authname = "SHA1";
    o->prng_hash = "SHA1";
    o->prng_nonce_secret_len = 16;
    o->replay = true;
    o->replay_window = DEFAULT_SEQ_BACKTRACK;
    o->replay_time = DEFAULT_TIME_BACKTRACK;
    o->key_direction = KEY_DIRECTION_BIDIRECTIONAL;
#ifdef ENABLE_PREDICTION_RESISTANCE
    o->use_prediction_resistance = false;
#endif
    o->key_method = 2;
    o->tls_timeout = 2;
    o->renegotiate_bytes = -1;
    o->renegotiate_seconds = 3600;
    o->renegotiate_seconds_min = -1;
    o->handshake_window = 60;
    o->transition_window = 3600;
    o->tls_cert_profile = NULL;
    o->ecdh_curve = NULL;
#ifdef ENABLE_X509ALTUSERNAME
    o->x509_username_field = X509_USERNAME_FIELD_DEFAULT;
#endif
#ifdef ENABLE_PKCS11
    o->pkcs11_pin_cache_period = -1;
#endif                  /* ENABLE_PKCS11 */

/* P2MP server context features */
#if P2MP_SERVER
    o->auth_token_generate = false;

    /* Set default --tmp-dir */
#ifdef _WIN32
    /* On Windows, find temp dir via environment variables */
    o->tmp_dir = win_get_tempdir();
#else
    /* Non-windows platforms use $TMPDIR, and if not set, default to '/tmp' */
    o->tmp_dir = getenv("TMPDIR");
    if (!o->tmp_dir)
    {
        o->tmp_dir = "/tmp";
    }
#endif /* _WIN32 */
#endif /* P2MP_SERVER */
    o->allow_recursive_routing = false;
}