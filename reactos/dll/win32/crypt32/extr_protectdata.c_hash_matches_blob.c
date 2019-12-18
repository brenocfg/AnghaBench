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
struct TYPE_4__ {scalar_t__ cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  TYPE_1__ DATA_BLOB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  convert_hash_to_blob (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static
BOOL hash_matches_blob(HCRYPTHASH hHash, const DATA_BLOB *two)
{
    BOOL rc = FALSE;
    DATA_BLOB one;

    if (!two || !two->pbData) return FALSE;

    if (!convert_hash_to_blob(hHash,&one)) {
        return FALSE;
    }

    if ( one.cbData == two->cbData &&
         memcmp( one.pbData, two->pbData, one.cbData ) == 0 )
    {
        rc = TRUE;
    }

    CryptMemFree(one.pbData);
    return rc;
}