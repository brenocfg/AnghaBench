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

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_IS_ENDIAN ; 
 scalar_t__ IS_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 int /*<<< orphan*/  swap_copy (unsigned char*,void const*,size_t) ; 

__attribute__((used)) static void le_copy(unsigned char *out, const void *in, size_t len)
{
    DECLARE_IS_ENDIAN;

    if (IS_LITTLE_ENDIAN)
        memcpy(out, in, len);
    else
        swap_copy(out, in, len);
}