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
struct dlm_rsb {int res_dir_nodeid; scalar_t__ res_nodeid; scalar_t__ res_master_nodeid; int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_first_lkid; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int ENOTBLK ; 
 scalar_t__ dlm_no_directory (struct dlm_ls*) ; 
 scalar_t__ dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_print_rsb (struct dlm_rsb*) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,scalar_t__,int,...) ; 

__attribute__((used)) static int validate_master_nodeid(struct dlm_ls *ls, struct dlm_rsb *r,
				  int from_nodeid)
{
	if (dlm_no_directory(ls)) {
		log_error(ls, "find_rsb keep from_nodeid %d master %d dir %d",
			  from_nodeid, r->res_master_nodeid,
			  r->res_dir_nodeid);
		dlm_print_rsb(r);
		return -ENOTBLK;
	}

	if (from_nodeid != r->res_dir_nodeid) {
		/* our rsb is not master, and another node (not the dir node)
	   	   has sent us a request.  this is much more common when our
	   	   master_nodeid is zero, so limit debug to non-zero.  */

		if (r->res_master_nodeid) {
			log_debug(ls, "validate master from_other %d master %d "
				  "dir %d first %x %s", from_nodeid,
				  r->res_master_nodeid, r->res_dir_nodeid,
				  r->res_first_lkid, r->res_name);
		}
		return -ENOTBLK;
	} else {
		/* our rsb is not master, but the dir nodeid has sent us a
	   	   request; this could happen with master 0 / res_nodeid -1 */

		if (r->res_master_nodeid) {
			log_error(ls, "validate master from_dir %d master %d "
				  "first %x %s",
				  from_nodeid, r->res_master_nodeid,
				  r->res_first_lkid, r->res_name);
		}

		r->res_master_nodeid = dlm_our_nodeid();
		r->res_nodeid = 0;
		return 0;
	}
}