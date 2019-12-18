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
typedef  int /*<<< orphan*/  uint8_t ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ openvpn_base64_encode (void const*,int,char**) ; 
 scalar_t__ string_alloc (char*,struct gc_arena*) ; 

uint8_t *
make_base64_string2(const uint8_t *str, int src_len, struct gc_arena *gc)
{
    uint8_t *ret = NULL;
    char *b64out = NULL;
    ASSERT(openvpn_base64_encode((const void *)str, src_len, &b64out) >= 0);
    ret = (uint8_t *) string_alloc(b64out, gc);
    free(b64out);
    return ret;
}