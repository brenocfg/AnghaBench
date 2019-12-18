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
struct f2fs_sb_info {int /*<<< orphan*/  iostat_lock; scalar_t__* write_iostat; int /*<<< orphan*/  iostat_enable; } ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;

/* Variables and functions */
 size_t APP_BUFFERED_IO ; 
 int APP_DIRECT_IO ; 
 int APP_WRITE_IO ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void f2fs_update_iostat(struct f2fs_sb_info *sbi,
			enum iostat_type type, unsigned long long io_bytes)
{
	if (!sbi->iostat_enable)
		return;
	spin_lock(&sbi->iostat_lock);
	sbi->write_iostat[type] += io_bytes;

	if (type == APP_WRITE_IO || type == APP_DIRECT_IO)
		sbi->write_iostat[APP_BUFFERED_IO] =
			sbi->write_iostat[APP_WRITE_IO] -
			sbi->write_iostat[APP_DIRECT_IO];
	spin_unlock(&sbi->iostat_lock);
}