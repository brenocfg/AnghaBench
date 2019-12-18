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
struct xfs_attr_list_context {int count; int seen_enough; int firstu; scalar_t__ alist; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
__xfs_xattr_put_listent(
	struct xfs_attr_list_context *context,
	char *prefix,
	int prefix_len,
	unsigned char *name,
	int namelen)
{
	char *offset;
	int arraytop;

	if (context->count < 0 || context->seen_enough)
		return;

	if (!context->alist)
		goto compute_size;

	arraytop = context->count + prefix_len + namelen + 1;
	if (arraytop > context->firstu) {
		context->count = -1;	/* insufficient space */
		context->seen_enough = 1;
		return;
	}
	offset = (char *)context->alist + context->count;
	strncpy(offset, prefix, prefix_len);
	offset += prefix_len;
	strncpy(offset, (char *)name, namelen);			/* real name */
	offset += namelen;
	*offset = '\0';

compute_size:
	context->count += prefix_len + namelen + 1;
	return;
}