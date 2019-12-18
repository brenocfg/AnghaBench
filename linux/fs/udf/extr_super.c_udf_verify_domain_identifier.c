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
struct super_block {int dummy; } ;
struct regid {int flags; scalar_t__ identSuffix; int /*<<< orphan*/  ident; } ;
struct domainEntityIDSuffix {int flags; } ;

/* Variables and functions */
 int EACCES ; 
 int ENTITYIDSUFFIX_FLAGS_HARDWRITEPROTECT ; 
 int ENTITYIDSUFFIX_FLAGS_SOFTWRITEPROTECT ; 
 int ENTITYID_FLAGS_DIRTY ; 
 int /*<<< orphan*/  UDF_FLAG_RW_INCOMPAT ; 
 int /*<<< orphan*/  UDF_ID_COMPLIANT ; 
 int /*<<< orphan*/  UDF_SET_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*,char*) ; 

__attribute__((used)) static int udf_verify_domain_identifier(struct super_block *sb,
					struct regid *ident, char *dname)
{
	struct domainEntityIDSuffix *suffix;

	if (memcmp(ident->ident, UDF_ID_COMPLIANT, strlen(UDF_ID_COMPLIANT))) {
		udf_warn(sb, "Not OSTA UDF compliant %s descriptor.\n", dname);
		goto force_ro;
	}
	if (ident->flags & (1 << ENTITYID_FLAGS_DIRTY)) {
		udf_warn(sb, "Possibly not OSTA UDF compliant %s descriptor.\n",
			 dname);
		goto force_ro;
	}
	suffix = (struct domainEntityIDSuffix *)ident->identSuffix;
	if (suffix->flags & (1 << ENTITYIDSUFFIX_FLAGS_HARDWRITEPROTECT) ||
	    suffix->flags & (1 << ENTITYIDSUFFIX_FLAGS_SOFTWRITEPROTECT)) {
		if (!sb_rdonly(sb)) {
			udf_warn(sb, "Descriptor for %s marked write protected."
				 " Forcing read only mount.\n", dname);
		}
		goto force_ro;
	}
	return 0;

force_ro:
	if (!sb_rdonly(sb))
		return -EACCES;
	UDF_SET_FLAG(sb, UDF_FLAG_RW_INCOMPAT);
	return 0;
}