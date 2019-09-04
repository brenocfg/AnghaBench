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
struct TYPE_2__ {int /*<<< orphan*/ * ff_type_map; } ;
struct fc_lport {TYPE_1__ fcts; } ;
typedef  enum fc_fh_type { ____Placeholder_fc_fh_type } fc_fh_type ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int FC_NS_BPW ; 
 int /*<<< orphan*/  htonl (unsigned long) ; 
 unsigned long ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_lport_add_fc4_type(struct fc_lport *lport, enum fc_fh_type type)
{
	__be32 *mp;

	mp = &lport->fcts.ff_type_map[type / FC_NS_BPW];
	*mp = htonl(ntohl(*mp) | 1UL << (type % FC_NS_BPW));
}