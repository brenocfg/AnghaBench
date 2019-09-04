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
typedef  scalar_t__ u8 ;
struct dst_entry {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct metadata_dst {int type; struct dst_entry dst; } ;
typedef  enum metadata_type { ____Placeholder_metadata_type } metadata_type ;

/* Variables and functions */
 int DST_METADATA ; 
 int DST_NOCOUNT ; 
 int /*<<< orphan*/  DST_OBSOLETE_NONE ; 
 int /*<<< orphan*/  dst_init (struct dst_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dst_md_discard ; 
 int /*<<< orphan*/  dst_md_discard_out ; 
 int /*<<< orphan*/  md_dst_ops ; 
 int /*<<< orphan*/  memset (struct dst_entry*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __metadata_dst_init(struct metadata_dst *md_dst,
				enum metadata_type type, u8 optslen)

{
	struct dst_entry *dst;

	dst = &md_dst->dst;
	dst_init(dst, &md_dst_ops, NULL, 1, DST_OBSOLETE_NONE,
		 DST_METADATA | DST_NOCOUNT);

	dst->input = dst_md_discard;
	dst->output = dst_md_discard_out;

	memset(dst + 1, 0, sizeof(*md_dst) + optslen - sizeof(*dst));
	md_dst->type = type;
}