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
typedef  int /*<<< orphan*/  u32 ;
struct bfa_fcoe_stats_s {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcport_fcoe_stats_swap(struct bfa_fcoe_stats_s *d,
	struct bfa_fcoe_stats_s *s)
{
	u32	*dip = (u32 *) d;
	__be32	*sip = (__be32 *) s;
	int		i;

	for (i = 0; i < ((sizeof(struct bfa_fcoe_stats_s))/sizeof(u32));
	     i = i + 2) {
#ifdef __BIG_ENDIAN
		dip[i] = be32_to_cpu(sip[i]);
		dip[i + 1] = be32_to_cpu(sip[i + 1]);
#else
		dip[i] = be32_to_cpu(sip[i + 1]);
		dip[i + 1] = be32_to_cpu(sip[i]);
#endif
	}
}