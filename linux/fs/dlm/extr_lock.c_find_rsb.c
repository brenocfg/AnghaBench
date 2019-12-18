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
typedef  int uint32_t ;
struct dlm_rsb {int dummy; } ;
struct dlm_ls {int ls_rsbtbl_size; } ;

/* Variables and functions */
 int DLM_RESNAME_MAXLEN ; 
 int EINVAL ; 
 int dlm_hash2nodeid (struct dlm_ls*,int) ; 
 scalar_t__ dlm_no_directory (struct dlm_ls*) ; 
 int find_rsb_dir (struct dlm_ls*,char*,int,int,int,int,int,unsigned int,struct dlm_rsb**) ; 
 int find_rsb_nodir (struct dlm_ls*,char*,int,int,int,int,int,unsigned int,struct dlm_rsb**) ; 
 int jhash (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_rsb(struct dlm_ls *ls, char *name, int len, int from_nodeid,
		    unsigned int flags, struct dlm_rsb **r_ret)
{
	uint32_t hash, b;
	int dir_nodeid;

	if (len > DLM_RESNAME_MAXLEN)
		return -EINVAL;

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	dir_nodeid = dlm_hash2nodeid(ls, hash);

	if (dlm_no_directory(ls))
		return find_rsb_nodir(ls, name, len, hash, b, dir_nodeid,
				      from_nodeid, flags, r_ret);
	else
		return find_rsb_dir(ls, name, len, hash, b, dir_nodeid,
				      from_nodeid, flags, r_ret);
}