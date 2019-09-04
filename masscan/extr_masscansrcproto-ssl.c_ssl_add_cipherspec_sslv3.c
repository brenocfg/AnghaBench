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
 unsigned char* REALLOC (void*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int ssl_hello_size (void*) ; 

__attribute__((used)) static char *
ssl_add_cipherspec_sslv3(void *templ, unsigned cipher_spec, unsigned is_append)
{
    unsigned char *px;
    size_t len0 = ssl_hello_size(templ);
    size_t len1;
    size_t len1b;
    size_t len2;
    size_t offset;
    size_t offset2;
    
    /* Increase space by 2 for additional cipherspec */
    px = REALLOC(templ, ssl_hello_size(templ) + 2);
    
    /* parse the lengths */
    len1 = px[3] << 8 | px[4];
    len1b = px[6] << 16 | px[7] << 8 | px[8];
    
    
    /* skip session id field */
    offset = 43;
    offset += px[offset] + 1;
    
    /* do cipherspecs */
    len2 = px[offset] << 8 | px[offset+1];
    offset2 = offset+2;
    if (is_append) {
        /* append to end of list */
        memmove(px + offset2 + len2 + 2,
                px + offset2 + len2,
                len0 - (offset2 + len2));
        px[offset2 + len2    ] = (unsigned char)(cipher_spec>>8);
        px[offset2 + len2 + 1] = (unsigned char)(cipher_spec>>0);
    } else {
        /* prepend to start of list, making this the prefered cipherspec*/
        memmove(px + offset2 + 2,
                px + offset2,
                len0 - offset2);
        px[offset2    ] = (unsigned char)(cipher_spec>>8);
        px[offset2 + 1] = (unsigned char)(cipher_spec>>0);
    }
    
    /* fix length fields */
    len2 += 2;
    px[offset    ] = (unsigned char)(len2>>8);
    px[offset + 1] = (unsigned char)(len2>>0);
    len1b += 2;
    px[6] = (unsigned char)(len1b>>16);
    px[7] = (unsigned char)(len1b>> 8);
    px[8] = (unsigned char)(len1b>> 0);
    len1 += 2;
    px[3] = (unsigned char)(len1>>8);
    px[4] = (unsigned char)(len1>>0);
    
    return (char*)px;    
}