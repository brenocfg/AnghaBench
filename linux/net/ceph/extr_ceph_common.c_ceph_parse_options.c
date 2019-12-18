#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* from; char const* to; } ;
typedef  TYPE_1__ substring_t ;
struct ceph_options {int /*<<< orphan*/  flags; void* osd_request_timeout; void* mount_timeout; void* osd_idle_ttl; void* osd_keepalive_timeout; void* key; void* name; int /*<<< orphan*/  fsid; int /*<<< orphan*/  my_addr; int /*<<< orphan*/  num_mon; int /*<<< orphan*/ * mon_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_MAX_MON ; 
 void* CEPH_MOUNT_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  CEPH_OPT_ABORT_ON_FULL ; 
 int /*<<< orphan*/  CEPH_OPT_DEFAULT ; 
 int /*<<< orphan*/  CEPH_OPT_FSID ; 
 int /*<<< orphan*/  CEPH_OPT_MYIP ; 
 int /*<<< orphan*/  CEPH_OPT_NOCRC ; 
 int /*<<< orphan*/  CEPH_OPT_NOMSGAUTH ; 
 int /*<<< orphan*/  CEPH_OPT_NOMSGSIGN ; 
 int /*<<< orphan*/  CEPH_OPT_NOSHARE ; 
 int /*<<< orphan*/  CEPH_OPT_TCP_NODELAY ; 
 void* CEPH_OSD_IDLE_TTL_DEFAULT ; 
 void* CEPH_OSD_KEEPALIVE_DEFAULT ; 
 void* CEPH_OSD_REQUEST_TIMEOUT_DEFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ceph_options* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_MAX ; 
 int MAX_OPT_ARGS ; 
#define  Opt_abort_on_full 148 
#define  Opt_cephx_require_signatures 147 
#define  Opt_cephx_sign_messages 146 
#define  Opt_crc 145 
#define  Opt_fsid 144 
#define  Opt_ip 143 
#define  Opt_key 142 
 int Opt_last_int ; 
 int Opt_last_string ; 
#define  Opt_mount_timeout 141 
#define  Opt_name 140 
#define  Opt_nocephx_require_signatures 139 
#define  Opt_nocephx_sign_messages 138 
#define  Opt_nocrc 137 
#define  Opt_noshare 136 
#define  Opt_notcp_nodelay 135 
#define  Opt_osd_idle_ttl 134 
#define  Opt_osd_request_timeout 133 
#define  Opt_osdkeepalivetimeout 132 
#define  Opt_osdtimeout 131 
#define  Opt_secret 130 
#define  Opt_share 129 
#define  Opt_tcp_nodelay 128 
 int /*<<< orphan*/  ceph_crypto_key_destroy (void*) ; 
 int ceph_crypto_key_unarmor (void*,char const*) ; 
 int /*<<< orphan*/  ceph_destroy_options (struct ceph_options*) ; 
 int ceph_parse_ips (char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int get_secret (void*,char const*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kstrndup (char const*,char const*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int match_int (TYPE_1__*,int*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  opt_tokens ; 
 int parse_fsid (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 char* strsep (char**,char*) ; 

struct ceph_options *
ceph_parse_options(char *options, const char *dev_name,
			const char *dev_name_end,
			int (*parse_extra_token)(char *c, void *private),
			void *private)
{
	struct ceph_options *opt;
	const char *c;
	int err = -ENOMEM;
	substring_t argstr[MAX_OPT_ARGS];

	opt = kzalloc(sizeof(*opt), GFP_KERNEL);
	if (!opt)
		return ERR_PTR(-ENOMEM);
	opt->mon_addr = kcalloc(CEPH_MAX_MON, sizeof(*opt->mon_addr),
				GFP_KERNEL);
	if (!opt->mon_addr)
		goto out;

	dout("parse_options %p options '%s' dev_name '%s'\n", opt, options,
	     dev_name);

	/* start with defaults */
	opt->flags = CEPH_OPT_DEFAULT;
	opt->osd_keepalive_timeout = CEPH_OSD_KEEPALIVE_DEFAULT;
	opt->mount_timeout = CEPH_MOUNT_TIMEOUT_DEFAULT;
	opt->osd_idle_ttl = CEPH_OSD_IDLE_TTL_DEFAULT;
	opt->osd_request_timeout = CEPH_OSD_REQUEST_TIMEOUT_DEFAULT;

	/* get mon ip(s) */
	/* ip1[:port1][,ip2[:port2]...] */
	err = ceph_parse_ips(dev_name, dev_name_end, opt->mon_addr,
			     CEPH_MAX_MON, &opt->num_mon);
	if (err < 0)
		goto out;

	/* parse mount options */
	while ((c = strsep(&options, ",")) != NULL) {
		int token, intval;
		if (!*c)
			continue;
		err = -EINVAL;
		token = match_token((char *)c, opt_tokens, argstr);
		if (token < 0 && parse_extra_token) {
			/* extra? */
			err = parse_extra_token((char *)c, private);
			if (err < 0) {
				pr_err("bad option at '%s'\n", c);
				goto out;
			}
			continue;
		}
		if (token < Opt_last_int) {
			err = match_int(&argstr[0], &intval);
			if (err < 0) {
				pr_err("bad option arg (not int) at '%s'\n", c);
				goto out;
			}
			dout("got int token %d val %d\n", token, intval);
		} else if (token > Opt_last_int && token < Opt_last_string) {
			dout("got string token %d val %s\n", token,
			     argstr[0].from);
		} else {
			dout("got token %d\n", token);
		}
		switch (token) {
		case Opt_ip:
			err = ceph_parse_ips(argstr[0].from,
					     argstr[0].to,
					     &opt->my_addr,
					     1, NULL);
			if (err < 0)
				goto out;
			opt->flags |= CEPH_OPT_MYIP;
			break;

		case Opt_fsid:
			err = parse_fsid(argstr[0].from, &opt->fsid);
			if (err == 0)
				opt->flags |= CEPH_OPT_FSID;
			break;
		case Opt_name:
			kfree(opt->name);
			opt->name = kstrndup(argstr[0].from,
					      argstr[0].to-argstr[0].from,
					      GFP_KERNEL);
			if (!opt->name) {
				err = -ENOMEM;
				goto out;
			}
			break;
		case Opt_secret:
			ceph_crypto_key_destroy(opt->key);
			kfree(opt->key);

		        opt->key = kzalloc(sizeof(*opt->key), GFP_KERNEL);
			if (!opt->key) {
				err = -ENOMEM;
				goto out;
			}
			err = ceph_crypto_key_unarmor(opt->key, argstr[0].from);
			if (err < 0)
				goto out;
			break;
		case Opt_key:
			ceph_crypto_key_destroy(opt->key);
			kfree(opt->key);

		        opt->key = kzalloc(sizeof(*opt->key), GFP_KERNEL);
			if (!opt->key) {
				err = -ENOMEM;
				goto out;
			}
			err = get_secret(opt->key, argstr[0].from);
			if (err < 0)
				goto out;
			break;

			/* misc */
		case Opt_osdtimeout:
			pr_warn("ignoring deprecated osdtimeout option\n");
			break;
		case Opt_osdkeepalivetimeout:
			/* 0 isn't well defined right now, reject it */
			if (intval < 1 || intval > INT_MAX / 1000) {
				pr_err("osdkeepalive out of range\n");
				err = -EINVAL;
				goto out;
			}
			opt->osd_keepalive_timeout =
					msecs_to_jiffies(intval * 1000);
			break;
		case Opt_osd_idle_ttl:
			/* 0 isn't well defined right now, reject it */
			if (intval < 1 || intval > INT_MAX / 1000) {
				pr_err("osd_idle_ttl out of range\n");
				err = -EINVAL;
				goto out;
			}
			opt->osd_idle_ttl = msecs_to_jiffies(intval * 1000);
			break;
		case Opt_mount_timeout:
			/* 0 is "wait forever" (i.e. infinite timeout) */
			if (intval < 0 || intval > INT_MAX / 1000) {
				pr_err("mount_timeout out of range\n");
				err = -EINVAL;
				goto out;
			}
			opt->mount_timeout = msecs_to_jiffies(intval * 1000);
			break;
		case Opt_osd_request_timeout:
			/* 0 is "wait forever" (i.e. infinite timeout) */
			if (intval < 0 || intval > INT_MAX / 1000) {
				pr_err("osd_request_timeout out of range\n");
				err = -EINVAL;
				goto out;
			}
			opt->osd_request_timeout = msecs_to_jiffies(intval * 1000);
			break;

		case Opt_share:
			opt->flags &= ~CEPH_OPT_NOSHARE;
			break;
		case Opt_noshare:
			opt->flags |= CEPH_OPT_NOSHARE;
			break;

		case Opt_crc:
			opt->flags &= ~CEPH_OPT_NOCRC;
			break;
		case Opt_nocrc:
			opt->flags |= CEPH_OPT_NOCRC;
			break;

		case Opt_cephx_require_signatures:
			opt->flags &= ~CEPH_OPT_NOMSGAUTH;
			break;
		case Opt_nocephx_require_signatures:
			opt->flags |= CEPH_OPT_NOMSGAUTH;
			break;
		case Opt_cephx_sign_messages:
			opt->flags &= ~CEPH_OPT_NOMSGSIGN;
			break;
		case Opt_nocephx_sign_messages:
			opt->flags |= CEPH_OPT_NOMSGSIGN;
			break;

		case Opt_tcp_nodelay:
			opt->flags |= CEPH_OPT_TCP_NODELAY;
			break;
		case Opt_notcp_nodelay:
			opt->flags &= ~CEPH_OPT_TCP_NODELAY;
			break;

		case Opt_abort_on_full:
			opt->flags |= CEPH_OPT_ABORT_ON_FULL;
			break;

		default:
			BUG_ON(token);
		}
	}

	/* success */
	return opt;

out:
	ceph_destroy_options(opt);
	return ERR_PTR(err);
}