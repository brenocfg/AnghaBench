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
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
struct TYPE_3__ {int* ga_bmval; } ;
struct TYPE_4__ {TYPE_1__ getattr; } ;
struct nfsd4_op {TYPE_2__ u; } ;

/* Variables and functions */
 int FATTR4_WORD0_ACL ; 
 int FATTR4_WORD0_FILEHANDLE ; 
 int FATTR4_WORD0_FS_LOCATIONS ; 
 int FATTR4_WORD1_OWNER ; 
 int FATTR4_WORD1_OWNER_GROUP ; 
 int FATTR4_WORD2_SECURITY_LABEL ; 
 scalar_t__ IDMAP_NAMESZ ; 
 scalar_t__ NFS4_FHSIZE ; 
 scalar_t__ NFS4_MAXLABELLEN ; 
 int hweight32 (int) ; 
 int svc_max_payload (struct svc_rqst*) ; 

__attribute__((used)) static inline u32 nfsd4_getattr_rsize(struct svc_rqst *rqstp,
				      struct nfsd4_op *op)
{
	u32 *bmap = op->u.getattr.ga_bmval;
	u32 bmap0 = bmap[0], bmap1 = bmap[1], bmap2 = bmap[2];
	u32 ret = 0;

	if (bmap0 & FATTR4_WORD0_ACL)
		return svc_max_payload(rqstp);
	if (bmap0 & FATTR4_WORD0_FS_LOCATIONS)
		return svc_max_payload(rqstp);

	if (bmap1 & FATTR4_WORD1_OWNER) {
		ret += IDMAP_NAMESZ + 4;
		bmap1 &= ~FATTR4_WORD1_OWNER;
	}
	if (bmap1 & FATTR4_WORD1_OWNER_GROUP) {
		ret += IDMAP_NAMESZ + 4;
		bmap1 &= ~FATTR4_WORD1_OWNER_GROUP;
	}
	if (bmap0 & FATTR4_WORD0_FILEHANDLE) {
		ret += NFS4_FHSIZE + 4;
		bmap0 &= ~FATTR4_WORD0_FILEHANDLE;
	}
	if (bmap2 & FATTR4_WORD2_SECURITY_LABEL) {
		ret += NFS4_MAXLABELLEN + 12;
		bmap2 &= ~FATTR4_WORD2_SECURITY_LABEL;
	}
	/*
	 * Largest of remaining attributes are 16 bytes (e.g.,
	 * supported_attributes)
	 */
	ret += 16 * (hweight32(bmap0) + hweight32(bmap1) + hweight32(bmap2));
	/* bitmask, length */
	ret += 20;
	return ret;
}