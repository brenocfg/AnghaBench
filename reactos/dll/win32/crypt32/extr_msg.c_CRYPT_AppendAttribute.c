#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cAttr; int /*<<< orphan*/ * rgAttr; } ;
typedef  TYPE_1__ CRYPT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  CRYPT_ATTRIBUTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_ConstructAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * CryptMemRealloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FALSE ; 

__attribute__((used)) static BOOL CRYPT_AppendAttribute(CRYPT_ATTRIBUTES *out,
 const CRYPT_ATTRIBUTE *in)
{
    BOOL ret = FALSE;

    out->rgAttr = CryptMemRealloc(out->rgAttr,
     (out->cAttr + 1) * sizeof(CRYPT_ATTRIBUTE));
    if (out->rgAttr)
    {
        ret = CRYPT_ConstructAttribute(&out->rgAttr[out->cAttr], in);
        if (ret)
            out->cAttr++;
    }
    return ret;
}