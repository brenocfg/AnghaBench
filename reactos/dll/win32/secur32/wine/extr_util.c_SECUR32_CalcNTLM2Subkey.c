#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  digest; } ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  TYPE_1__ MD5_CTX ;
typedef  unsigned char BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (TYPE_1__*) ; 
 int /*<<< orphan*/  MD5Init (TYPE_1__*) ; 
 int /*<<< orphan*/  MD5Update (TYPE_1__*,unsigned char const*,int) ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SECUR32_CalcNTLM2Subkey(const BYTE *session_key, const char *magic, PBYTE subkey)
{
    MD5_CTX ctx;

    MD5Init(&ctx);
    MD5Update(&ctx, session_key, 16);
    MD5Update(&ctx, (const unsigned char*)magic, lstrlenA(magic)+1);
    MD5Final(&ctx);
    memcpy(subkey, ctx.digest, 16);
}