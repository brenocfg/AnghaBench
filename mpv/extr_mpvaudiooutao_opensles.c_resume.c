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
struct priv {int /*<<< orphan*/  buffer_queue; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_callback (int /*<<< orphan*/ ,struct ao*) ; 

__attribute__((used)) static void resume(struct ao *ao)
{
    struct priv *p = ao->priv;
    buffer_callback(p->buffer_queue, ao);
}