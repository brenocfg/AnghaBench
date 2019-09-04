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
struct mp_priv {int /*<<< orphan*/  pallocated_mp_xmitframe_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int free_mp_priv(struct mp_priv *pmp_priv)
{
	kfree(pmp_priv->pallocated_mp_xmitframe_buf);
	return 0;
}