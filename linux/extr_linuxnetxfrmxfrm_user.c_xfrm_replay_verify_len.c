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
struct xfrm_replay_state_esn {int bmp_len; int replay_window; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EINVAL ; 
 struct xfrm_replay_state_esn* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 unsigned int xfrm_replay_state_esn_len (struct xfrm_replay_state_esn*) ; 

__attribute__((used)) static inline int xfrm_replay_verify_len(struct xfrm_replay_state_esn *replay_esn,
					 struct nlattr *rp)
{
	struct xfrm_replay_state_esn *up;
	unsigned int ulen;

	if (!replay_esn || !rp)
		return 0;

	up = nla_data(rp);
	ulen = xfrm_replay_state_esn_len(up);

	/* Check the overall length and the internal bitmap length to avoid
	 * potential overflow. */
	if (nla_len(rp) < (int)ulen ||
	    xfrm_replay_state_esn_len(replay_esn) != ulen ||
	    replay_esn->bmp_len != up->bmp_len)
		return -EINVAL;

	if (up->replay_window > up->bmp_len * sizeof(__u32) * 8)
		return -EINVAL;

	return 0;
}