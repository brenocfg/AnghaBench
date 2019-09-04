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
struct cifs_tcon {int dummy; } ;
struct cifs_search_info {int dummy; } ;
struct cifs_fid {int /*<<< orphan*/  netfid; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int CIFSFindNext (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_search_info*) ; 

__attribute__((used)) static int
cifs_query_dir_next(const unsigned int xid, struct cifs_tcon *tcon,
		    struct cifs_fid *fid, __u16 search_flags,
		    struct cifs_search_info *srch_inf)
{
	return CIFSFindNext(xid, tcon, fid->netfid, search_flags, srch_inf);
}