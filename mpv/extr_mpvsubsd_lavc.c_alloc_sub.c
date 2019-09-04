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
struct sub {int valid; scalar_t__ id; scalar_t__ src_h; scalar_t__ src_w; scalar_t__ count; } ;
struct sd_lavc_priv {int /*<<< orphan*/  new_id; struct sub* subs; } ;

/* Variables and functions */
 int MAX_QUEUE ; 
 int /*<<< orphan*/  clear_sub (struct sub*) ; 

__attribute__((used)) static void alloc_sub(struct sd_lavc_priv *priv)
{
    clear_sub(&priv->subs[MAX_QUEUE - 1]);
    struct sub tmp = priv->subs[MAX_QUEUE - 1];
    for (int n = MAX_QUEUE - 1; n > 0; n--)
        priv->subs[n] = priv->subs[n - 1];
    priv->subs[0] = tmp;
    // clear only some fields; the memory allocs can be reused
    priv->subs[0].valid = false;
    priv->subs[0].count = 0;
    priv->subs[0].src_w = 0;
    priv->subs[0].src_h = 0;
    priv->subs[0].id = priv->new_id++;
}