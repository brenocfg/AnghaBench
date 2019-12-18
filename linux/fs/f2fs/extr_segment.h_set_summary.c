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
struct f2fs_summary {unsigned char version; int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_summary(struct f2fs_summary *sum, nid_t nid,
			unsigned int ofs_in_node, unsigned char version)
{
	sum->nid = cpu_to_le32(nid);
	sum->ofs_in_node = cpu_to_le16(ofs_in_node);
	sum->version = version;
}