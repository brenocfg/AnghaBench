#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct policydb_compat_info {int ocon_num; } ;
struct policydb {struct ocontext** ocontexts; } ;
struct TYPE_10__ {int port; int /*<<< orphan*/  dev_name; } ;
struct TYPE_9__ {int low_pkey; int high_pkey; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_8__ {int* addr; int* mask; } ;
struct TYPE_12__ {int addr; int mask; } ;
struct TYPE_11__ {void* high_port; void* low_port; void* protocol; } ;
struct TYPE_14__ {TYPE_3__ ibendport; TYPE_2__ ibpkey; TYPE_1__ node6; int /*<<< orphan*/  name; TYPE_5__ node; TYPE_4__ port; } ;
struct TYPE_13__ {void* behavior; } ;
struct ocontext {int /*<<< orphan*/ * context; TYPE_7__ u; TYPE_6__ v; void** sid; struct ocontext* next; } ;
typedef  int __le32 ;
typedef  int __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  OCON_FS 136 
#define  OCON_FSUSE 135 
#define  OCON_IBENDPORT 134 
#define  OCON_IBPKEY 133 
#define  OCON_ISID 132 
#define  OCON_NETIF 131 
#define  OCON_NODE 130 
#define  OCON_NODE6 129 
#define  OCON_PORT 128 
 void* SECURITY_FS_USE_MAX ; 
 void* SECURITY_FS_USE_MNTPOINT ; 
 int U16_MAX ; 
 int U8_MAX ; 
 int /*<<< orphan*/  be64_to_cpu (int) ; 
 int context_read_and_validate (int /*<<< orphan*/ *,struct policydb*,void*) ; 
 struct ocontext* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int) ; 
 int next_entry (int*,void*,int) ; 
 int str_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int ocontext_read(struct policydb *p, struct policydb_compat_info *info,
			 void *fp)
{
	int i, j, rc;
	u32 nel, len;
	__be64 prefixbuf[1];
	__le32 buf[3];
	struct ocontext *l, *c;
	u32 nodebuf[8];

	for (i = 0; i < info->ocon_num; i++) {
		rc = next_entry(buf, fp, sizeof(u32));
		if (rc)
			goto out;
		nel = le32_to_cpu(buf[0]);

		l = NULL;
		for (j = 0; j < nel; j++) {
			rc = -ENOMEM;
			c = kzalloc(sizeof(*c), GFP_KERNEL);
			if (!c)
				goto out;
			if (l)
				l->next = c;
			else
				p->ocontexts[i] = c;
			l = c;

			switch (i) {
			case OCON_ISID:
				rc = next_entry(buf, fp, sizeof(u32));
				if (rc)
					goto out;

				c->sid[0] = le32_to_cpu(buf[0]);
				rc = context_read_and_validate(&c->context[0], p, fp);
				if (rc)
					goto out;
				break;
			case OCON_FS:
			case OCON_NETIF:
				rc = next_entry(buf, fp, sizeof(u32));
				if (rc)
					goto out;
				len = le32_to_cpu(buf[0]);

				rc = str_read(&c->u.name, GFP_KERNEL, fp, len);
				if (rc)
					goto out;

				rc = context_read_and_validate(&c->context[0], p, fp);
				if (rc)
					goto out;
				rc = context_read_and_validate(&c->context[1], p, fp);
				if (rc)
					goto out;
				break;
			case OCON_PORT:
				rc = next_entry(buf, fp, sizeof(u32)*3);
				if (rc)
					goto out;
				c->u.port.protocol = le32_to_cpu(buf[0]);
				c->u.port.low_port = le32_to_cpu(buf[1]);
				c->u.port.high_port = le32_to_cpu(buf[2]);
				rc = context_read_and_validate(&c->context[0], p, fp);
				if (rc)
					goto out;
				break;
			case OCON_NODE:
				rc = next_entry(nodebuf, fp, sizeof(u32) * 2);
				if (rc)
					goto out;
				c->u.node.addr = nodebuf[0]; /* network order */
				c->u.node.mask = nodebuf[1]; /* network order */
				rc = context_read_and_validate(&c->context[0], p, fp);
				if (rc)
					goto out;
				break;
			case OCON_FSUSE:
				rc = next_entry(buf, fp, sizeof(u32)*2);
				if (rc)
					goto out;

				rc = -EINVAL;
				c->v.behavior = le32_to_cpu(buf[0]);
				/* Determined at runtime, not in policy DB. */
				if (c->v.behavior == SECURITY_FS_USE_MNTPOINT)
					goto out;
				if (c->v.behavior > SECURITY_FS_USE_MAX)
					goto out;

				len = le32_to_cpu(buf[1]);
				rc = str_read(&c->u.name, GFP_KERNEL, fp, len);
				if (rc)
					goto out;

				rc = context_read_and_validate(&c->context[0], p, fp);
				if (rc)
					goto out;
				break;
			case OCON_NODE6: {
				int k;

				rc = next_entry(nodebuf, fp, sizeof(u32) * 8);
				if (rc)
					goto out;
				for (k = 0; k < 4; k++)
					c->u.node6.addr[k] = nodebuf[k];
				for (k = 0; k < 4; k++)
					c->u.node6.mask[k] = nodebuf[k+4];
				rc = context_read_and_validate(&c->context[0], p, fp);
				if (rc)
					goto out;
				break;
			}
			case OCON_IBPKEY: {
				u32 pkey_lo, pkey_hi;

				rc = next_entry(prefixbuf, fp, sizeof(u64));
				if (rc)
					goto out;

				/* we need to have subnet_prefix in CPU order */
				c->u.ibpkey.subnet_prefix = be64_to_cpu(prefixbuf[0]);

				rc = next_entry(buf, fp, sizeof(u32) * 2);
				if (rc)
					goto out;

				pkey_lo = le32_to_cpu(buf[0]);
				pkey_hi = le32_to_cpu(buf[1]);

				if (pkey_lo > U16_MAX || pkey_hi > U16_MAX) {
					rc = -EINVAL;
					goto out;
				}

				c->u.ibpkey.low_pkey  = pkey_lo;
				c->u.ibpkey.high_pkey = pkey_hi;

				rc = context_read_and_validate(&c->context[0],
							       p,
							       fp);
				if (rc)
					goto out;
				break;
			}
			case OCON_IBENDPORT: {
				u32 port;

				rc = next_entry(buf, fp, sizeof(u32) * 2);
				if (rc)
					goto out;
				len = le32_to_cpu(buf[0]);

				rc = str_read(&c->u.ibendport.dev_name, GFP_KERNEL, fp, len);
				if (rc)
					goto out;

				port = le32_to_cpu(buf[1]);
				if (port > U8_MAX || port == 0) {
					rc = -EINVAL;
					goto out;
				}

				c->u.ibendport.port = port;

				rc = context_read_and_validate(&c->context[0],
							       p,
							       fp);
				if (rc)
					goto out;
				break;
			} /* end case */
			} /* end switch */
		}
	}
	rc = 0;
out:
	return rc;
}