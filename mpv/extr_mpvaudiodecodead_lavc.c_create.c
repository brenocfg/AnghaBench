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
struct mp_decoder {struct mp_filter* f; } ;
struct priv {struct mp_decoder public; } ;
struct mp_filter {struct priv* priv; int /*<<< orphan*/  log; } ;
struct mp_codec_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  ad_lavc_filter ; 
 int /*<<< orphan*/  init (struct mp_filter*,struct mp_codec_params*,char const*) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_log_new (struct mp_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mp_filter*) ; 

__attribute__((used)) static struct mp_decoder *create(struct mp_filter *parent,
                                 struct mp_codec_params *codec,
                                 const char *decoder)
{
    struct mp_filter *da = mp_filter_create(parent, &ad_lavc_filter);
    if (!da)
        return NULL;

    mp_filter_add_pin(da, MP_PIN_IN, "in");
    mp_filter_add_pin(da, MP_PIN_OUT, "out");

    da->log = mp_log_new(da, parent->log, NULL);

    struct priv *priv = da->priv;
    priv->public.f = da;

    if (!init(da, codec, decoder)) {
        talloc_free(da);
        return NULL;
    }
    return &priv->public;
}