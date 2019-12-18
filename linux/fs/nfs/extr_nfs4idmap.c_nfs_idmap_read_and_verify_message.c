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
struct key {int dummy; } ;
struct idmap_msg {scalar_t__ im_type; int im_conv; char* im_name; int /*<<< orphan*/  im_id; } ;
typedef  int /*<<< orphan*/  id_str ;

/* Variables and functions */
 int EINVAL ; 
 int ENOKEY ; 
#define  IDMAP_CONV_IDTONAME 129 
#define  IDMAP_CONV_NAMETOID 128 
 int NFS_UINT_MAXLEN ; 
 int nfs_idmap_instantiate (struct key*,struct key*,char*,size_t) ; 
 int /*<<< orphan*/  nfs_map_numeric_to_string (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int nfs_idmap_read_and_verify_message(struct idmap_msg *im,
		struct idmap_msg *upcall,
		struct key *key, struct key *authkey)
{
	char id_str[NFS_UINT_MAXLEN];
	size_t len;
	int ret = -ENOKEY;

	/* ret = -ENOKEY */
	if (upcall->im_type != im->im_type || upcall->im_conv != im->im_conv)
		goto out;
	switch (im->im_conv) {
	case IDMAP_CONV_NAMETOID:
		if (strcmp(upcall->im_name, im->im_name) != 0)
			break;
		/* Note: here we store the NUL terminator too */
		len = 1 + nfs_map_numeric_to_string(im->im_id, id_str,
						    sizeof(id_str));
		ret = nfs_idmap_instantiate(key, authkey, id_str, len);
		break;
	case IDMAP_CONV_IDTONAME:
		if (upcall->im_id != im->im_id)
			break;
		len = strlen(im->im_name);
		ret = nfs_idmap_instantiate(key, authkey, im->im_name, len);
		break;
	default:
		ret = -EINVAL;
	}
out:
	return ret;
}