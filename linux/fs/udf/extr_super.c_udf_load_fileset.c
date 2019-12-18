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
struct super_block {int dummy; } ;
struct kernel_lb_addr {int /*<<< orphan*/  partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct TYPE_5__ {int /*<<< orphan*/  tagSerialNum; } ;
struct TYPE_4__ {int /*<<< orphan*/  extLocation; } ;
struct fileSetDesc {TYPE_2__ descTag; TYPE_1__ rootDirectoryICB; int /*<<< orphan*/  domainIdent; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_serial_number; } ;

/* Variables and functions */
 TYPE_3__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct kernel_lb_addr lelb_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udf_verify_domain_identifier (struct super_block*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int udf_load_fileset(struct super_block *sb, struct fileSetDesc *fset,
			    struct kernel_lb_addr *root)
{
	int ret;

	ret = udf_verify_domain_identifier(sb, &fset->domainIdent, "file set");
	if (ret < 0)
		return ret;

	*root = lelb_to_cpu(fset->rootDirectoryICB.extLocation);
	UDF_SB(sb)->s_serial_number = le16_to_cpu(fset->descTag.tagSerialNum);

	udf_debug("Rootdir at block=%u, partition=%u\n",
		  root->logicalBlockNum, root->partitionReferenceNum);
	return 0;
}