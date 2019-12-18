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
typedef  int /*<<< orphan*/  tunnel_cfg ;
struct udp_tunnel_sock_cfg {int encap_type; int /*<<< orphan*/  gro_complete; int /*<<< orphan*/  gro_receive; int /*<<< orphan*/  encap_rcv; int /*<<< orphan*/ * encap_destroy; struct fou* sk_user_data; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; int /*<<< orphan*/  local_udp_port; } ;
struct fou_cfg {int type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  flags; TYPE_1__ udp_config; } ;
struct fou {int type; int /*<<< orphan*/  protocol; struct socket* sock; int /*<<< orphan*/  flags; int /*<<< orphan*/  family; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  FOU_ENCAP_DIRECT 129 
#define  FOU_ENCAP_GUE 128 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fou_add_to_port_list (struct net*,struct fou*,struct fou_cfg*) ; 
 int /*<<< orphan*/  fou_gro_complete ; 
 int /*<<< orphan*/  fou_gro_receive ; 
 int /*<<< orphan*/  fou_udp_recv ; 
 int /*<<< orphan*/  gue_gro_complete ; 
 int /*<<< orphan*/  gue_gro_receive ; 
 int /*<<< orphan*/  gue_udp_recv ; 
 int /*<<< orphan*/  kfree (struct fou*) ; 
 struct fou* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct udp_tunnel_sock_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_udp_tunnel_sock (struct net*,struct socket*,struct udp_tunnel_sock_cfg*) ; 
 int udp_sock_create (struct net*,TYPE_1__*,struct socket**) ; 
 int /*<<< orphan*/  udp_tunnel_sock_release (struct socket*) ; 

__attribute__((used)) static int fou_create(struct net *net, struct fou_cfg *cfg,
		      struct socket **sockp)
{
	struct socket *sock = NULL;
	struct fou *fou = NULL;
	struct sock *sk;
	struct udp_tunnel_sock_cfg tunnel_cfg;
	int err;

	/* Open UDP socket */
	err = udp_sock_create(net, &cfg->udp_config, &sock);
	if (err < 0)
		goto error;

	/* Allocate FOU port structure */
	fou = kzalloc(sizeof(*fou), GFP_KERNEL);
	if (!fou) {
		err = -ENOMEM;
		goto error;
	}

	sk = sock->sk;

	fou->port = cfg->udp_config.local_udp_port;
	fou->family = cfg->udp_config.family;
	fou->flags = cfg->flags;
	fou->type = cfg->type;
	fou->sock = sock;

	memset(&tunnel_cfg, 0, sizeof(tunnel_cfg));
	tunnel_cfg.encap_type = 1;
	tunnel_cfg.sk_user_data = fou;
	tunnel_cfg.encap_destroy = NULL;

	/* Initial for fou type */
	switch (cfg->type) {
	case FOU_ENCAP_DIRECT:
		tunnel_cfg.encap_rcv = fou_udp_recv;
		tunnel_cfg.gro_receive = fou_gro_receive;
		tunnel_cfg.gro_complete = fou_gro_complete;
		fou->protocol = cfg->protocol;
		break;
	case FOU_ENCAP_GUE:
		tunnel_cfg.encap_rcv = gue_udp_recv;
		tunnel_cfg.gro_receive = gue_gro_receive;
		tunnel_cfg.gro_complete = gue_gro_complete;
		break;
	default:
		err = -EINVAL;
		goto error;
	}

	setup_udp_tunnel_sock(net, sock, &tunnel_cfg);

	sk->sk_allocation = GFP_ATOMIC;

	err = fou_add_to_port_list(net, fou, cfg);
	if (err)
		goto error;

	if (sockp)
		*sockp = sock;

	return 0;

error:
	kfree(fou);
	if (sock)
		udp_tunnel_sock_release(sock);

	return err;
}