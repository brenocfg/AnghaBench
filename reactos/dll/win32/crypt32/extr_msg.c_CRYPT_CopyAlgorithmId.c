#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Parameters; scalar_t__ pszObjId; } ;
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ LPBYTE ;
typedef  TYPE_1__ CRYPT_ALGORITHM_IDENTIFIER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_CopyBlob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static inline void CRYPT_CopyAlgorithmId(CRYPT_ALGORITHM_IDENTIFIER *out,
 const CRYPT_ALGORITHM_IDENTIFIER *in, LPBYTE *nextData)
{
    if (in->pszObjId)
    {
        out->pszObjId = (LPSTR)*nextData;
        strcpy(out->pszObjId, in->pszObjId);
        *nextData += strlen(out->pszObjId) + 1;
    }
    CRYPT_CopyBlob(&out->Parameters, &in->Parameters, nextData);
}