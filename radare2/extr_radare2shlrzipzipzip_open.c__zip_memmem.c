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
 scalar_t__ memchr (unsigned char const*,unsigned char const,size_t) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,size_t) ; 

__attribute__((used)) static unsigned char *
_zip_memmem(const unsigned char *big, size_t biglen, const unsigned char *little, size_t littlelen)
{
    const unsigned char *p;
    
    if ((biglen < littlelen) || (littlelen == 0))
	return NULL;
    p = big-1;
    while ((p=(const unsigned char *)
	        memchr(p+1, little[0], (size_t)(big-(p+1))+(size_t)(biglen-littlelen)+1)) != NULL) {
	if (memcmp(p+1, little+1, littlelen-1)==0)
	    return (unsigned char *)p;
    }

    return NULL;
}