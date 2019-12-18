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
struct mp_hwupload {struct mp_filter* f; } ;
struct priv {struct mp_hwupload public; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  hwupload_filter ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe_formats (struct mp_hwupload*,int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_filter*) ; 

struct mp_hwupload *mp_hwupload_create(struct mp_filter *parent, int hw_imgfmt)
{
    struct mp_filter *f = mp_filter_create(parent, &hwupload_filter);
    if (!f)
        return NULL;

    struct priv *p = f->priv;
    struct mp_hwupload *u = &p->public;
    u->f = f;

    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    if (!probe_formats(u, hw_imgfmt)) {
        MP_ERR(f, "hardware format not supported\n");
        goto error;
    }

    return u;
error:
    talloc_free(f);
    return NULL;
}