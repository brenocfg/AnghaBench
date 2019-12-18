#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nodetype; union jffs2_sum_mem* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  version; int /*<<< orphan*/  xid; } ;
struct TYPE_6__ {int /*<<< orphan*/  ino; int /*<<< orphan*/  nsize; } ;
struct TYPE_5__ {int /*<<< orphan*/  inode; } ;
union jffs2_sum_mem {TYPE_4__ u; TYPE_3__ x; TYPE_2__ d; TYPE_1__ i; } ;
struct jffs2_summary {int /*<<< orphan*/  sum_num; int /*<<< orphan*/  sum_size; union jffs2_sum_mem* sum_list_tail; union jffs2_sum_mem* sum_list_head; } ;

/* Variables and functions */
#define  JFFS2_NODETYPE_DIRENT 131 
#define  JFFS2_NODETYPE_INODE 130 
#define  JFFS2_NODETYPE_XATTR 129 
#define  JFFS2_NODETYPE_XREF 128 
 int /*<<< orphan*/  JFFS2_SUMMARY_DIRENT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_INODE_SIZE ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_XATTR_SIZE ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_XREF_SIZE ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int) ; 
 int /*<<< orphan*/  dbg_summary (char*,...) ; 
 int je16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  je32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jffs2_sum_add_mem(struct jffs2_summary *s, union jffs2_sum_mem *item)
{
	if (!s->sum_list_head)
		s->sum_list_head = (union jffs2_sum_mem *) item;
	if (s->sum_list_tail)
		s->sum_list_tail->u.next = (union jffs2_sum_mem *) item;
	s->sum_list_tail = (union jffs2_sum_mem *) item;

	switch (je16_to_cpu(item->u.nodetype)) {
		case JFFS2_NODETYPE_INODE:
			s->sum_size += JFFS2_SUMMARY_INODE_SIZE;
			s->sum_num++;
			dbg_summary("inode (%u) added to summary\n",
						je32_to_cpu(item->i.inode));
			break;
		case JFFS2_NODETYPE_DIRENT:
			s->sum_size += JFFS2_SUMMARY_DIRENT_SIZE(item->d.nsize);
			s->sum_num++;
			dbg_summary("dirent (%u) added to summary\n",
						je32_to_cpu(item->d.ino));
			break;
#ifdef CONFIG_JFFS2_FS_XATTR
		case JFFS2_NODETYPE_XATTR:
			s->sum_size += JFFS2_SUMMARY_XATTR_SIZE;
			s->sum_num++;
			dbg_summary("xattr (xid=%u, version=%u) added to summary\n",
				    je32_to_cpu(item->x.xid), je32_to_cpu(item->x.version));
			break;
		case JFFS2_NODETYPE_XREF:
			s->sum_size += JFFS2_SUMMARY_XREF_SIZE;
			s->sum_num++;
			dbg_summary("xref added to summary\n");
			break;
#endif
		default:
			JFFS2_WARNING("UNKNOWN node type %u\n",
					    je16_to_cpu(item->u.nodetype));
			return 1;
	}
	return 0;
}