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
struct priv {int /*<<< orphan*/  opt_cache; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  feed_packet (struct priv*) ; 
 int /*<<< orphan*/  m_config_cache_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_frame (struct priv*) ; 

__attribute__((used)) static void process(struct mp_filter *f)
{
    struct priv *p = f->priv;
    m_config_cache_update(p->opt_cache);

    feed_packet(p);
    read_frame(p);
}