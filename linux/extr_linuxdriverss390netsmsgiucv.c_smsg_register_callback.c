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
struct smsg_callback {char const* prefix; void (* callback ) (char const*,char*) ;int /*<<< orphan*/  list; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct smsg_callback* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsg_list ; 
 int /*<<< orphan*/  smsg_list_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int smsg_register_callback(const char *prefix,
			   void (*callback)(const char *from, char *str))
{
	struct smsg_callback *cb;

	cb = kmalloc(sizeof(struct smsg_callback), GFP_KERNEL);
	if (!cb)
		return -ENOMEM;
	cb->prefix = prefix;
	cb->len = strlen(prefix);
	cb->callback = callback;
	spin_lock_bh(&smsg_list_lock);
	list_add_tail(&cb->list, &smsg_list);
	spin_unlock_bh(&smsg_list_lock);
	return 0;
}