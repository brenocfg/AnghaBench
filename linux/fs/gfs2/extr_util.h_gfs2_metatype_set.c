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
typedef  int /*<<< orphan*/  u16 ;
struct gfs2_meta_header {void* mh_format; void* mh_type; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gfs2_metatype_set(struct buffer_head *bh, u16 type,
				     u16 format)
{
	struct gfs2_meta_header *mh;
	mh = (struct gfs2_meta_header *)bh->b_data;
	mh->mh_type = cpu_to_be32(type);
	mh->mh_format = cpu_to_be32(format);
}