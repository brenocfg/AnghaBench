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
 int EVP_EncodeBlock (unsigned char*,void const*,size_t) ; 
 char* app_malloc (size_t,char*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static char *base64encode (const void *buf, size_t len)
{
    int i;
    size_t outl;
    char  *out;

    /* Calculate size of encoded data */
    outl = (len / 3);
    if (len % 3 > 0)
        outl++;
    outl <<= 2;
    out = app_malloc(outl + 1, "base64 encode buffer");

    i = EVP_EncodeBlock((unsigned char *)out, buf, len);
    assert(i <= (int)outl);
    if (i < 0)
        *out = '\0';
    return out;
}