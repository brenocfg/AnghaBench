#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ logicalBlockNum; } ;
struct TYPE_4__ {scalar_t__* i_data; } ;
struct udf_inode_info {int i_lenEAttr; TYPE_3__ i_location; TYPE_1__ i_ext; } ;
struct inode {int dummy; } ;
struct genericFormat {scalar_t__ attrSubtype; int /*<<< orphan*/  attrLength; int /*<<< orphan*/  attrType; } ;
struct TYPE_5__ {scalar_t__ tagIdent; int /*<<< orphan*/  tagLocation; } ;
struct extendedAttrHeaderDesc {int /*<<< orphan*/  appAttrLocation; int /*<<< orphan*/  impAttrLocation; TYPE_2__ descTag; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAG_IDENT_EAHD ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

struct genericFormat *udf_get_extendedattr(struct inode *inode, uint32_t type,
					   uint8_t subtype)
{
	struct genericFormat *gaf;
	uint8_t *ea = NULL;
	uint32_t offset;
	struct udf_inode_info *iinfo = UDF_I(inode);

	ea = iinfo->i_ext.i_data;

	if (iinfo->i_lenEAttr) {
		struct extendedAttrHeaderDesc *eahd;
		eahd = (struct extendedAttrHeaderDesc *)ea;

		/* check checksum/crc */
		if (eahd->descTag.tagIdent !=
				cpu_to_le16(TAG_IDENT_EAHD) ||
		    le32_to_cpu(eahd->descTag.tagLocation) !=
				iinfo->i_location.logicalBlockNum)
			return NULL;

		if (type < 2048)
			offset = sizeof(struct extendedAttrHeaderDesc);
		else if (type < 65536)
			offset = le32_to_cpu(eahd->impAttrLocation);
		else
			offset = le32_to_cpu(eahd->appAttrLocation);

		while (offset < iinfo->i_lenEAttr) {
			gaf = (struct genericFormat *)&ea[offset];
			if (le32_to_cpu(gaf->attrType) == type &&
					gaf->attrSubtype == subtype)
				return gaf;
			else
				offset += le32_to_cpu(gaf->attrLength);
		}
	}

	return NULL;
}