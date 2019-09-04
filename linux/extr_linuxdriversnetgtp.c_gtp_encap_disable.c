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
struct gtp_dev {int /*<<< orphan*/  sk1u; int /*<<< orphan*/  sk0; } ;

/* Variables and functions */
 int /*<<< orphan*/  gtp_encap_disable_sock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gtp_encap_disable(struct gtp_dev *gtp)
{
	gtp_encap_disable_sock(gtp->sk0);
	gtp_encap_disable_sock(gtp->sk1u);
}