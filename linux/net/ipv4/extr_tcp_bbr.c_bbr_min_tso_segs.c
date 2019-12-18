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
typedef  int u32 ;
struct sock {int sk_pacing_rate; } ;

/* Variables and functions */
 int bbr_min_tso_rate ; 

__attribute__((used)) static u32 bbr_min_tso_segs(struct sock *sk)
{
	return sk->sk_pacing_rate < (bbr_min_tso_rate >> 3) ? 1 : 2;
}