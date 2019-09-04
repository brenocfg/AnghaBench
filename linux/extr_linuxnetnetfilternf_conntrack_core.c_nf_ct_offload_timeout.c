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
struct nf_conn {scalar_t__ timeout; } ;

/* Variables and functions */
 int DAY ; 
 int nf_ct_expires (struct nf_conn*) ; 
 scalar_t__ nfct_time_stamp ; 

__attribute__((used)) static void nf_ct_offload_timeout(struct nf_conn *ct)
{
	if (nf_ct_expires(ct) < DAY / 2)
		ct->timeout = nfct_time_stamp + DAY;
}