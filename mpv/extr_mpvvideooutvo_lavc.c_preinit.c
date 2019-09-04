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
struct vo {int /*<<< orphan*/  log; int /*<<< orphan*/  encode_lavc_ctx; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_VIDEO ; 
 int /*<<< orphan*/  encoder_context_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_steal (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct priv *vc = vo->priv;
    vc->enc = encoder_context_alloc(vo->encode_lavc_ctx, STREAM_VIDEO, vo->log);
    if (!vc->enc)
        return -1;
    talloc_steal(vc, vc->enc);
    return 0;
}