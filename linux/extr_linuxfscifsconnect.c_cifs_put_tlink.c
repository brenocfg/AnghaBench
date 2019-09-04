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
struct tcon_link {int /*<<< orphan*/  tl_time; int /*<<< orphan*/  tl_flags; int /*<<< orphan*/  tl_count; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  TCON_LINK_IN_TREE ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_put_tcon (struct tcon_link*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct tcon_link*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tcon_link* tlink_tcon (struct tcon_link*) ; 

void
cifs_put_tlink(struct tcon_link *tlink)
{
	if (!tlink || IS_ERR(tlink))
		return;

	if (!atomic_dec_and_test(&tlink->tl_count) ||
	    test_bit(TCON_LINK_IN_TREE, &tlink->tl_flags)) {
		tlink->tl_time = jiffies;
		return;
	}

	if (!IS_ERR(tlink_tcon(tlink)))
		cifs_put_tcon(tlink_tcon(tlink));
	kfree(tlink);
	return;
}