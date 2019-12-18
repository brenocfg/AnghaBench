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
struct ipv6_opt_hdr {int hdrlen; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct ipv6_opt_hdr* kmemdup (struct ipv6_opt_hdr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ipv6_opt_hdr *ip6_opt_dup(struct ipv6_opt_hdr *src,
					       gfp_t gfp)
{
	return src ? kmemdup(src, (src->hdrlen + 1) * 8, gfp) : NULL;
}