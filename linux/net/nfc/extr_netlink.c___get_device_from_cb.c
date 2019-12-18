#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct nfc_dev {int dummy; } ;
struct netlink_callback {int /*<<< orphan*/  nlh; } ;
struct TYPE_3__ {int /*<<< orphan*/  maxattr; scalar_t__ hdrsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct nfc_dev* ERR_PTR (int) ; 
 scalar_t__ GENL_HDRLEN ; 
 size_t NFC_ATTR_DEVICE_INDEX ; 
 struct nlattr** genl_family_attrbuf (TYPE_1__*) ; 
 TYPE_1__ nfc_genl_family ; 
 int /*<<< orphan*/  nfc_genl_policy ; 
 struct nfc_dev* nfc_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nlmsg_parse_deprecated (int /*<<< orphan*/ ,scalar_t__,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfc_dev *__get_device_from_cb(struct netlink_callback *cb)
{
	struct nlattr **attrbuf = genl_family_attrbuf(&nfc_genl_family);
	struct nfc_dev *dev;
	int rc;
	u32 idx;

	rc = nlmsg_parse_deprecated(cb->nlh,
				    GENL_HDRLEN + nfc_genl_family.hdrsize,
				    attrbuf, nfc_genl_family.maxattr,
				    nfc_genl_policy, NULL);
	if (rc < 0)
		return ERR_PTR(rc);

	if (!attrbuf[NFC_ATTR_DEVICE_INDEX])
		return ERR_PTR(-EINVAL);

	idx = nla_get_u32(attrbuf[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		return ERR_PTR(-ENODEV);

	return dev;
}