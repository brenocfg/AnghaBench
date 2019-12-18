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
typedef  int /*<<< orphan*/  finishedlabel ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int tls13_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

int tls13_derive_finishedkey(SSL *s, const EVP_MD *md,
                             const unsigned char *secret,
                             unsigned char *fin, size_t finlen)
{
#ifdef CHARSET_EBCDIC
  static const unsigned char finishedlabel[] = { 0x66, 0x69, 0x6E, 0x69, 0x73, 0x68, 0x65, 0x64, 0x00 };
#else
  static const unsigned char finishedlabel[] = "finished";
#endif

    return tls13_hkdf_expand(s, md, secret, finishedlabel,
                             sizeof(finishedlabel) - 1, NULL, 0, fin, finlen, 1);
}