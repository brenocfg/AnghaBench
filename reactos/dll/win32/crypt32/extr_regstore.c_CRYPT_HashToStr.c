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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  const* LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void CRYPT_HashToStr(const BYTE *hash, LPWSTR asciiHash)
{
    static const WCHAR fmt[] = { '%','0','2','X',0 };
    DWORD i;

    assert(hash);
    assert(asciiHash);

    for (i = 0; i < 20; i++)
        wsprintfW(asciiHash + i * 2, fmt, hash[i]);
}