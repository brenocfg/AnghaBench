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
struct X500TokenW {int end; int start; } ;
struct KeynameKeeper {int keyLen; char* keyName; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_FreeKeynameKeeper (struct KeynameKeeper*) ; 
 char* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

__attribute__((used)) static void CRYPT_KeynameKeeperFromTokenW(struct KeynameKeeper *keeper,
 const struct X500TokenW *key)
{
    DWORD len = key->end - key->start;

    if (len >= keeper->keyLen)
    {
        CRYPT_FreeKeynameKeeper( keeper );
        keeper->keyLen = len + 1;
        keeper->keyName = CryptMemAlloc(keeper->keyLen * sizeof(WCHAR));
    }
    memcpy(keeper->keyName, key->start, len * sizeof(WCHAR));
    keeper->keyName[len] = '\0';
    TRACE("Keyname is %s\n", debugstr_w(keeper->keyName));
}