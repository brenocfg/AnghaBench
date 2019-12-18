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
struct xfrm_replay_state_esn {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct xfrm_replay_state_esn*) ; 
 struct xfrm_replay_state_esn* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfrm_replay_state_esn*,struct xfrm_replay_state_esn*,unsigned int) ; 
 struct xfrm_replay_state_esn* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 unsigned int xfrm_replay_state_esn_len (struct xfrm_replay_state_esn*) ; 

__attribute__((used)) static int xfrm_alloc_replay_state_esn(struct xfrm_replay_state_esn **replay_esn,
				       struct xfrm_replay_state_esn **preplay_esn,
				       struct nlattr *rta)
{
	struct xfrm_replay_state_esn *p, *pp, *up;
	unsigned int klen, ulen;

	if (!rta)
		return 0;

	up = nla_data(rta);
	klen = xfrm_replay_state_esn_len(up);
	ulen = nla_len(rta) >= (int)klen ? klen : sizeof(*up);

	p = kzalloc(klen, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	pp = kzalloc(klen, GFP_KERNEL);
	if (!pp) {
		kfree(p);
		return -ENOMEM;
	}

	memcpy(p, up, ulen);
	memcpy(pp, up, ulen);

	*replay_esn = p;
	*preplay_esn = pp;

	return 0;
}