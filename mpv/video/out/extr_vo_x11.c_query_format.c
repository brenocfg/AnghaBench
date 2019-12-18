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
struct priv {int /*<<< orphan*/  sws; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFMT_RGB0 ; 
 scalar_t__ mp_sws_supports_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int query_format(struct vo *vo, int format)
{
    struct priv *p = vo->priv;
    if (mp_sws_supports_formats(p->sws, IMGFMT_RGB0, format))
        return 1;
    return 0;
}