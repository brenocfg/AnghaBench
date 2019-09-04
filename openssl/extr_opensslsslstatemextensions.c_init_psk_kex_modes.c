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
struct TYPE_4__ {int /*<<< orphan*/  psk_kex_mode; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  TLSEXT_KEX_MODE_FLAG_NONE ; 

__attribute__((used)) static int init_psk_kex_modes(SSL *s, unsigned int context)
{
    s->ext.psk_kex_mode = TLSEXT_KEX_MODE_FLAG_NONE;
    return 1;
}