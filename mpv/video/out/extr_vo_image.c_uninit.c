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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  current; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_image_unrefp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;

    mp_image_unrefp(&p->current);
}