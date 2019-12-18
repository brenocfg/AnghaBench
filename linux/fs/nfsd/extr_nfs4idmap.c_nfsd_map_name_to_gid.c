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
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAP_TYPE_GROUP ; 
 int /*<<< orphan*/  do_name_to_id (struct svc_rqst*,int /*<<< orphan*/ ,char const*,size_t,int*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsd_user_namespace (struct svc_rqst*) ; 
 int /*<<< orphan*/  nfserr_badowner ; 
 int /*<<< orphan*/  nfserr_inval ; 

__be32
nfsd_map_name_to_gid(struct svc_rqst *rqstp, const char *name, size_t namelen,
		kgid_t *gid)
{
	__be32 status;
	u32 id = -1;

	if (name == NULL || namelen == 0)
		return nfserr_inval;

	status = do_name_to_id(rqstp, IDMAP_TYPE_GROUP, name, namelen, &id);
	*gid = make_kgid(nfsd_user_namespace(rqstp), id);
	if (!gid_valid(*gid))
		status = nfserr_badowner;
	return status;
}