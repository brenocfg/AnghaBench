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
struct priv {int data_length; int /*<<< orphan*/  fp; } ;
struct ao {int sstride; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (void*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int play(struct ao *ao, void **data, int samples, int flags)
{
    struct priv *priv = ao->priv;
    int len = samples * ao->sstride;

    fwrite(data[0], len, 1, priv->fp);
    priv->data_length += len;
    return samples;
}