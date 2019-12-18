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
typedef  unsigned int u32 ;
struct ocfs2_write_ctxt {unsigned int w_cpos; unsigned int w_clen; int w_large_pages; int /*<<< orphan*/  w_unwritten_list; int /*<<< orphan*/  w_dealloc; int /*<<< orphan*/  w_type; struct buffer_head* w_di_bh; int /*<<< orphan*/  w_first_new_cpos; } ;
struct ocfs2_super {unsigned int s_clustersize_bits; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ocfs2_write_type_t ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct ocfs2_write_ctxt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ocfs2_alloc_write_ctxt(struct ocfs2_write_ctxt **wcp,
				  struct ocfs2_super *osb, loff_t pos,
				  unsigned len, ocfs2_write_type_t type,
				  struct buffer_head *di_bh)
{
	u32 cend;
	struct ocfs2_write_ctxt *wc;

	wc = kzalloc(sizeof(struct ocfs2_write_ctxt), GFP_NOFS);
	if (!wc)
		return -ENOMEM;

	wc->w_cpos = pos >> osb->s_clustersize_bits;
	wc->w_first_new_cpos = UINT_MAX;
	cend = (pos + len - 1) >> osb->s_clustersize_bits;
	wc->w_clen = cend - wc->w_cpos + 1;
	get_bh(di_bh);
	wc->w_di_bh = di_bh;
	wc->w_type = type;

	if (unlikely(PAGE_SHIFT > osb->s_clustersize_bits))
		wc->w_large_pages = 1;
	else
		wc->w_large_pages = 0;

	ocfs2_init_dealloc_ctxt(&wc->w_dealloc);
	INIT_LIST_HEAD(&wc->w_unwritten_list);

	*wcp = wc;

	return 0;
}