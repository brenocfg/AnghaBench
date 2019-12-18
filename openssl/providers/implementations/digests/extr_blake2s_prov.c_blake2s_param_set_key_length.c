#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  key_length; } ;
typedef  TYPE_1__ BLAKE2S_PARAM ;

/* Variables and functions */

void blake2s_param_set_key_length(BLAKE2S_PARAM *P, uint8_t keylen)
{
    P->key_length = keylen;
}