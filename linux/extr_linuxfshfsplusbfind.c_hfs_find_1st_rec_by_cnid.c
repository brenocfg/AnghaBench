#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct hfs_find_data {TYPE_9__* search_key; TYPE_7__* key; } ;
struct hfs_bnode {TYPE_5__* tree; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_17__ {scalar_t__ cnid; } ;
struct TYPE_13__ {scalar_t__ parent; } ;
struct TYPE_11__ {scalar_t__ cnid; } ;
struct TYPE_18__ {TYPE_8__ attr; TYPE_4__ cat; TYPE_2__ ext; } ;
struct TYPE_15__ {scalar_t__ cnid; } ;
struct TYPE_12__ {scalar_t__ parent; } ;
struct TYPE_10__ {scalar_t__ cnid; } ;
struct TYPE_16__ {TYPE_6__ attr; TYPE_3__ cat; TYPE_1__ ext; } ;
struct TYPE_14__ {scalar_t__ cnid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HFSPLUS_ATTR_CNID ; 
 scalar_t__ HFSPLUS_CAT_CNID ; 
 scalar_t__ HFSPLUS_EXT_CNID ; 
 scalar_t__ be32_to_cpu (scalar_t__) ; 

int hfs_find_1st_rec_by_cnid(struct hfs_bnode *bnode,
				struct hfs_find_data *fd,
				int *begin,
				int *end,
				int *cur_rec)
{
	__be32 cur_cnid;
	__be32 search_cnid;

	if (bnode->tree->cnid == HFSPLUS_EXT_CNID) {
		cur_cnid = fd->key->ext.cnid;
		search_cnid = fd->search_key->ext.cnid;
	} else if (bnode->tree->cnid == HFSPLUS_CAT_CNID) {
		cur_cnid = fd->key->cat.parent;
		search_cnid = fd->search_key->cat.parent;
	} else if (bnode->tree->cnid == HFSPLUS_ATTR_CNID) {
		cur_cnid = fd->key->attr.cnid;
		search_cnid = fd->search_key->attr.cnid;
	} else {
		cur_cnid = 0;	/* used-uninitialized warning */
		search_cnid = 0;
		BUG();
	}

	if (cur_cnid == search_cnid) {
		(*end) = (*cur_rec);
		if ((*begin) == (*end))
			return 1;
	} else {
		if (be32_to_cpu(cur_cnid) < be32_to_cpu(search_cnid))
			(*begin) = (*cur_rec) + 1;
		else
			(*end) = (*cur_rec) - 1;
	}

	return 0;
}