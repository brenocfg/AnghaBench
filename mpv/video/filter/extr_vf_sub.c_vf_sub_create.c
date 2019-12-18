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
struct priv {int /*<<< orphan*/  pool; int /*<<< orphan*/  opts; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_pool_new (struct priv*) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 int /*<<< orphan*/  talloc_steal (struct priv*,void*) ; 
 int /*<<< orphan*/  vf_sub_filter ; 

__attribute__((used)) static struct mp_filter *vf_sub_create(struct mp_filter *parent, void *options)
{
    struct mp_filter *f = mp_filter_create(parent, &vf_sub_filter);
    if (!f) {
        talloc_free(options);
        return NULL;
    }

    MP_WARN(f, "This filter is deprecated and will be removed (no replacement)\n");

    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    struct priv *priv = f->priv;
    priv->opts = talloc_steal(priv, options);
    priv->pool = mp_image_pool_new(priv);

    return f;
}