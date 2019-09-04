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
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int wsm_find_complete_indication(struct cw1200_common *priv,
					struct wsm_buf *buf)
{
	pr_warn("Implement find_complete_indication\n");
	return 0;
}