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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_selector {int dummy; } ;
struct xfrm_migrate {int dummy; } ;
struct xfrm_kmaddress {int dummy; } ;
struct xfrm_encap_tmpl {int dummy; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 

__attribute__((used)) static int xfrm_send_migrate(const struct xfrm_selector *sel, u8 dir, u8 type,
			     const struct xfrm_migrate *m, int num_migrate,
			     const struct xfrm_kmaddress *k,
			     const struct xfrm_encap_tmpl *encap)
{
	return -ENOPROTOOPT;
}