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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  (* cbc128_f ) (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub2 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub3 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int) ; 

size_t CRYPTO_nistcts128_encrypt(const unsigned char *in, unsigned char *out,
                                 size_t len, const void *key,
                                 unsigned char ivec[16], cbc128_f cbc)
{
    size_t residue;
    union {
        size_t align;
        unsigned char c[16];
    } tmp;

    if (len < 16)
        return 0;

    residue = len % 16;

    len -= residue;

    (*cbc) (in, out, len, key, ivec, 1);

    if (residue == 0)
        return len;

    in += len;
    out += len;

#if defined(CBC_HANDLES_TRUNCATED_IO)
    (*cbc) (in, out - 16 + residue, residue, key, ivec, 1);
#else
    memset(tmp.c, 0, sizeof(tmp));
    memcpy(tmp.c, in, residue);
    (*cbc) (tmp.c, out - 16 + residue, 16, key, ivec, 1);
#endif
    return len + residue;
}