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
typedef  int /*<<< orphan*/  md_kt_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_SHOW_KEY_SOURCE ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 scalar_t__ gc_malloc (int,int,struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/ * md_kt_get (char*) ; 
 int /*<<< orphan*/  secure_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls1_P_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
tls1_PRF(const uint8_t *label,
         int label_len,
         const uint8_t *sec,
         int slen,
         uint8_t *out1,
         int olen)
{
    struct gc_arena gc = gc_new();
    const md_kt_t *md5 = md_kt_get("MD5");
    const md_kt_t *sha1 = md_kt_get("SHA1");
    int len,i;
    const uint8_t *S1,*S2;
    uint8_t *out2;

    out2 = (uint8_t *) gc_malloc(olen, false, &gc);

    len = slen/2;
    S1 = sec;
    S2 = &(sec[len]);
    len += (slen&1); /* add for odd, make longer */

    tls1_P_hash(md5,S1,len,label,label_len,out1,olen);
    tls1_P_hash(sha1,S2,len,label,label_len,out2,olen);

    for (i = 0; i<olen; i++)
    {
        out1[i] ^= out2[i];
    }

    secure_memzero(out2, olen);

    dmsg(D_SHOW_KEY_SOURCE, "tls1_PRF out[%d]: %s", olen, format_hex(out1, olen, 0, &gc));

    gc_free(&gc);
}