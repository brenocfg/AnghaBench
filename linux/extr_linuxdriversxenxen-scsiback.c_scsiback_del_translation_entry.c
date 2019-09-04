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
struct vscsibk_info {int /*<<< orphan*/  v2p_lock; } ;
struct v2p_entry {int dummy; } ;
struct ids_tuple {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __scsiback_del_translation_entry (struct v2p_entry*) ; 
 struct v2p_entry* scsiback_chk_translation_entry (struct vscsibk_info*,struct ids_tuple*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int scsiback_del_translation_entry(struct vscsibk_info *info,
					  struct ids_tuple *v)
{
	struct v2p_entry *entry;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&info->v2p_lock, flags);
	/* Find out the translation entry specified */
	entry = scsiback_chk_translation_entry(info, v);
	if (entry)
		__scsiback_del_translation_entry(entry);
	else
		ret = -ENOENT;

	spin_unlock_irqrestore(&info->v2p_lock, flags);
	return ret;
}