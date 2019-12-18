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
struct tcon_link {int dummy; } ;
struct cifs_sb_info {struct tcon_link* master_tlink; } ;

/* Variables and functions */

__attribute__((used)) static inline struct tcon_link *
cifs_sb_master_tlink(struct cifs_sb_info *cifs_sb)
{
	return cifs_sb->master_tlink;
}