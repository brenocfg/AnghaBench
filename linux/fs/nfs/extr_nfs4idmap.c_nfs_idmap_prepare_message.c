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
typedef  int /*<<< orphan*/  substring_t ;
struct rpc_pipe_msg {int len; struct idmap_msg* data; } ;
struct idmap_msg {int /*<<< orphan*/  im_id; int /*<<< orphan*/  im_conv; void* im_type; int /*<<< orphan*/  im_name; } ;
struct idmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IDMAP_CONV_IDTONAME ; 
 int /*<<< orphan*/  IDMAP_CONV_NAMETOID ; 
 int /*<<< orphan*/  IDMAP_NAMESZ ; 
 void* IDMAP_TYPE_GROUP ; 
 void* IDMAP_TYPE_USER ; 
#define  Opt_find_gid 131 
#define  Opt_find_group 130 
#define  Opt_find_uid 129 
#define  Opt_find_user 128 
 int match_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int match_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_idmap_tokens ; 

__attribute__((used)) static int nfs_idmap_prepare_message(char *desc, struct idmap *idmap,
				     struct idmap_msg *im,
				     struct rpc_pipe_msg *msg)
{
	substring_t substr;
	int token, ret;

	im->im_type = IDMAP_TYPE_GROUP;
	token = match_token(desc, nfs_idmap_tokens, &substr);

	switch (token) {
	case Opt_find_uid:
		im->im_type = IDMAP_TYPE_USER;
		/* Fall through */
	case Opt_find_gid:
		im->im_conv = IDMAP_CONV_NAMETOID;
		ret = match_strlcpy(im->im_name, &substr, IDMAP_NAMESZ);
		break;

	case Opt_find_user:
		im->im_type = IDMAP_TYPE_USER;
		/* Fall through */
	case Opt_find_group:
		im->im_conv = IDMAP_CONV_IDTONAME;
		ret = match_int(&substr, &im->im_id);
		if (ret)
			goto out;
		break;

	default:
		ret = -EINVAL;
		goto out;
	}

	msg->data = im;
	msg->len  = sizeof(struct idmap_msg);

out:
	return ret;
}