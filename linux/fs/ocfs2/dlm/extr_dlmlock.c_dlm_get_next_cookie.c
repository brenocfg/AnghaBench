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
typedef  int u8 ;
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_cookie_lock ; 
 int dlm_next_cookie ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dlm_get_next_cookie(u8 node_num, u64 *cookie)
{
	u64 tmpnode = node_num;

	/* shift single byte of node num into top 8 bits */
	tmpnode <<= 56;

	spin_lock(&dlm_cookie_lock);
	*cookie = (dlm_next_cookie | tmpnode);
	if (++dlm_next_cookie & 0xff00000000000000ull) {
		mlog(0, "This node's cookie will now wrap!\n");
		dlm_next_cookie = 1;
	}
	spin_unlock(&dlm_cookie_lock);
}