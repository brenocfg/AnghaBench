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
struct priv {int num_entries; TYPE_1__* entries; } ;
struct mp_filter {struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  print; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f_reset(struct mp_filter *f)
{
    struct priv *p = f->priv;

    for (int n = 0; n < p->num_entries; n++)
        talloc_free(p->entries[n].print);
    p->num_entries = 0;
}