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
 int equal_case (unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equal_nocase (unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int equal_email(const unsigned char *a, size_t a_len,
                       const unsigned char *b, size_t b_len,
                       unsigned int unused_flags)
{
    size_t i = a_len;
    if (a_len != b_len)
        return 0;
    /*
     * We search backwards for the '@' character, so that we do not have to
     * deal with quoted local-parts.  The domain part is compared in a
     * case-insensitive manner.
     */
    while (i > 0) {
        --i;
        if (a[i] == '@' || b[i] == '@') {
            if (!equal_nocase(a + i, a_len - i, b + i, a_len - i, 0))
                return 0;
            break;
        }
    }
    if (i == 0)
        i = a_len;
    return equal_case(a, i, b, i, 0);
}