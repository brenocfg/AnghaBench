#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int blocksize; } ;
struct TYPE_5__ {TYPE_1__ audio_in; } ;
typedef  TYPE_2__ priv_t ;

/* Variables and functions */

__attribute__((used)) static int get_audio_framesize(priv_t *priv)
{
    return priv->audio_in.blocksize;
}