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
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 unsigned char* banout_string (struct BannerOutput*,unsigned int) ; 
 size_t banout_string_length (struct BannerOutput*,unsigned int) ; 
 scalar_t__ memcmp (unsigned char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
banout_string_equals(struct BannerOutput *banout, unsigned proto,
                     const char *rhs)
{
    const unsigned char *lhs = banout_string(banout, proto);
    size_t lhs_length = banout_string_length(banout, proto);
    size_t rhs_length = strlen(rhs);
    
    if (lhs_length != rhs_length)
        return 0;
    return memcmp(lhs, rhs, rhs_length) == 0;
}