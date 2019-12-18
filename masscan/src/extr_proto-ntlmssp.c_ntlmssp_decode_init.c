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
struct NtlmsspDecode {unsigned int length; int /*<<< orphan*/ * buf; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct NtlmsspDecode*,int /*<<< orphan*/ ,int) ; 

void
ntlmssp_decode_init(struct NtlmsspDecode *x, size_t length)
{
    memset(x, 0, sizeof(*x));
    
    /* [security] Double-check this input, since it's ultimately driven by user-input.
     * The code that leads to here should already have double-checked this, but I'm
     * doing it again just in case. This is larger than any input that should be
     * seen in the real world that a hacker isn't messing with.
     */
    if (length > 65536)
        length = 65536;
    
    x->length = (unsigned)length;
    x->offset = 0;
    x->buf = NULL;
    
}