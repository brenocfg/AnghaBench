#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  pkey; int /*<<< orphan*/  subnet_prefix; } ;
struct sel_ib_pkey {TYPE_1__ psec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sel_ib_pkey* kzalloc (int,int /*<<< orphan*/ ) ; 
 int security_ib_pkey_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sel_ib_pkey* sel_ib_pkey_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sel_ib_pkey_insert (struct sel_ib_pkey*) ; 
 int /*<<< orphan*/  sel_ib_pkey_lock ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sel_ib_pkey_sid_slow(u64 subnet_prefix, u16 pkey_num, u32 *sid)
{
	int ret;
	struct sel_ib_pkey *pkey;
	struct sel_ib_pkey *new = NULL;
	unsigned long flags;

	spin_lock_irqsave(&sel_ib_pkey_lock, flags);
	pkey = sel_ib_pkey_find(subnet_prefix, pkey_num);
	if (pkey) {
		*sid = pkey->psec.sid;
		spin_unlock_irqrestore(&sel_ib_pkey_lock, flags);
		return 0;
	}

	ret = security_ib_pkey_sid(&selinux_state, subnet_prefix, pkey_num,
				   sid);
	if (ret)
		goto out;

	/* If this memory allocation fails still return 0. The SID
	 * is valid, it just won't be added to the cache.
	 */
	new = kzalloc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		goto out;

	new->psec.subnet_prefix = subnet_prefix;
	new->psec.pkey = pkey_num;
	new->psec.sid = *sid;
	sel_ib_pkey_insert(new);

out:
	spin_unlock_irqrestore(&sel_ib_pkey_lock, flags);
	return ret;
}